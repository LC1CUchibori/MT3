
#define NOMINMAX
#include <Novice.h>
#include"Debug.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include "imgui.h"
const char kWindowTitle[] = "LE2C_04_ウチボリ_ユウタ";
int kWindowWidth = 1280;
int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };
	Vector3 cameraPosition{ 0.0f, 1.0f, -5.0f };

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};
	Sphere sphere[3];
	sphere[0].center = translates[0];
	sphere[1].center = translates[1];
	sphere[2].center = translates[2];
	sphere[0].radius = 0.1f;
	sphere[1].radius = 0.1f;
	sphere[2].radius = 0.1f;
	static bool isDebugCamera = false;
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector2Int mouse;
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			isDebugCamera = !isDebugCamera;
		}
		CameraMove(cameraRotate, cameraTranslate, mouse, isDebugCamera);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, Add(cameraPosition, cameraTranslate));
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 ViewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		// 回転行列を生成
		Matrix4x4 rotateMatrix = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

		Matrix4x4 SRT0 = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 SRT1 = MakeAffineMatrix(scales[1], rotates[1], translates[1]);
		Matrix4x4 SRT2 = MakeAffineMatrix(scales[2], rotates[2], translates[2]);
		Matrix4x4 L0 = SRT0;
		Matrix4x4 L1 = Multiply(SRT1, L0);
		Matrix4x4 L2 = Multiply(SRT2, L1);

		Vector3 translations[3];
		translations[0] = { L0.m[3][0],L0.m[3][1],L0.m[3][2] };
		translations[1] = { L1.m[3][0],L1.m[3][1],L1.m[3][2] };
		translations[2] = { L2.m[3][0],L2.m[3][1],L2.m[3][2] };

		Vector3 transformedPrev0 = Transform(translations[0], ViewProjectionMatrix);
		transformedPrev0 = Transform(transformedPrev0, viewportMatrix);
		Vector3 transformedPrev1 = Transform(translations[1], ViewProjectionMatrix);
		transformedPrev1 = Transform(transformedPrev1, viewportMatrix);
		Vector3 transformedPrev2 = Transform(translations[2], ViewProjectionMatrix);
		transformedPrev2 = Transform(transformedPrev2, viewportMatrix);
		sphere[0].center = translations[0];
		sphere[1].center = translations[1];
		sphere[2].center = translations[2];

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("CameraPosition", &cameraPosition.x, 0.01f);

		ImGui::DragFloat3("translates0", &translates[0].x, 0.01f);
		ImGui::DragFloat3("rotate0", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("translates1", &translates[1].x, 0.01f);
		ImGui::DragFloat3("rotate1", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("translates2", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotate2", &rotates[2].x, 0.01f);

		ImGui::End();

		DrawSphere(sphere[0], ViewProjectionMatrix, viewportMatrix, RED);
		DrawSphere(sphere[1], ViewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere(sphere[2], ViewProjectionMatrix, viewportMatrix, BLUE);

		Novice::DrawLine(static_cast<int>(transformedPrev0.x), static_cast<int>(transformedPrev0.y),
			static_cast<int>(transformedPrev1.x), static_cast<int>(transformedPrev1.y), WHITE);
		Novice::DrawLine(static_cast<int>(transformedPrev1.x), static_cast<int>(transformedPrev1.y),
			static_cast<int>(transformedPrev2.x), static_cast<int>(transformedPrev2.y), WHITE);
		DrawGrid(ViewProjectionMatrix, viewportMatrix);
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
