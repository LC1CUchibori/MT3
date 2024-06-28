#include <Novice.h>
#include <cstdint>
#include <corecrt_math_defines.h>
#include "Matrix.h"
#include <imgui.h>

struct Sphere
{
	Vector3 center; // 中心点
	float radius;   // 半径
};

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		float x = -kGridHalfWidth + (xIndex * kGridEvery);
		unsigned int color = 0xAAAAAAFF;
		Vector3 start{ x,0.0f,-kGridHalfWidth };
		Vector3 end{ x,0.0f,kGridHalfWidth };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		if (x == 0.0f)
		{
			color = BLACK;
		}

		Novice::DrawLine(int(startScreen.x),int(startScreen.y),int(endScreen.x),int(endScreen.y),color);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		float z = -kGridHalfWidth + (zIndex * kGridEvery);
		unsigned int  color = 0xAAAAAAFF;

		Vector3 start{ z,0.0f,-kGridHalfWidth };
		Vector3 end{ z,0.0f,kGridHalfWidth };

		Vector3 startScreen = Transform(Transform(start, viewProjectionMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectionMatrix), viewportMatrix);

		if (z == 0.0f)
		{
			color = BLACK;
		}

		Novice::DrawLine(int(startScreen.x),int(startScreen.y),int(endScreen.x),int(endScreen.y),(int)color);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 10;                          // 分割数
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = float(M_PI) / kSubdivision;        // 緯度分割1つ分の角度

	// 緯度の方向に分割 -π/2 ～ π/2
	for (uint32_t latIndex = 0; latIndex <= kSubdivision; ++latIndex)
	{
		float lat0 = float(M_PI) * (1.0f + kLatEvery*(float)latIndex / kSubdivision);
		float z0 = sphere.radius * sin(lat0);
		float zr0 = sphere.radius * cos(lat0);

		float lat1 = float(M_PI) * (1.0f +kLatEvery* (float)(latIndex + 1) / kSubdivision);
		float z1 = sphere.radius * sin(lat1);
		float zr1 = sphere.radius * cos(lat1);

		// 経度の方向に分割 0 ～ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			float lon0 = lonIndex * kLonEvery;
			float x0 = zr0 * cos(lon0);
			float y0 = zr0 * sin(lon0);

			float lon1 = (lonIndex + 1) * kLonEvery; // lonIndex の計算式を修正
			float x1 = zr1 * cos(lon1);
			float y1 = zr1 * sin(lon1);

			// a のワールド座標系での位置を計算
			Vector3 aWorld;
			aWorld.x = sphere.center.x + x0;
			aWorld.y = sphere.center.y + y0;
			aWorld.z = sphere.center.z + z0;

			// b のワールド座標系での位置を計算
			Vector3 bWorld;
			bWorld.x = sphere.center.x + x1;
			bWorld.y = sphere.center.y + y1;
			bWorld.z = sphere.center.z + z1;

			// c のワールド座標系での位置を計算
			Vector3 cWorld;
			cWorld.x = sphere.center.x + x0;
			cWorld.y = sphere.center.y + y0;
			cWorld.z = sphere.center.z + z1;

			// a のスクリーン座標系での位置を計算
			Vector3 aScreen = Transform(Transform(aWorld, viewProjectionMatrix), viewportMatrix);

			// b のスクリーン座標系での位置を計算
			Vector3 bScreen = Transform(Transform(bWorld, viewProjectionMatrix), viewportMatrix);

			// c のスクリーン座標系での位置を計算
			Vector3 cScreen = Transform(Transform(cWorld, viewProjectionMatrix), viewportMatrix);

			// a, b, c をスクリーン座標系で描画
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(bScreen.x), int(bScreen.y), color);
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(cScreen.x), int(cScreen.y), color);
			Novice::DrawLine(int(bScreen.x), int(bScreen.y), int(cScreen.x), int(cScreen.y), color);
		}
	}
}


const char kWindowTitle[] = "LE2C_ウチボリ_ユウタ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };
	Vector3 cameraPosition{ 0.0f, 1.0f, -5.0f };

	Sphere sphere;
	sphere.center = { 0, 0, 0 };
	sphere.radius = 1;

	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, Add(cameraPosition, cameraTranslate));
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 ViewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(ViewProjectionMatrix, viewportMatrix);

		// 球体の描画
		DrawSphere(sphere, ViewProjectionMatrix, viewportMatrix, BLACK); // 赤色で描画
		
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("CameraPosition", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
