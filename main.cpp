
#include <Novice.h>
#include"Debug.h"
#include <math.h>
#define _USE_MATH_DEFINES
#include "imgui.h"
#include <Vector2Int.h>
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
	AABB aabb[2];
	aabb[0].min = { -0.5f,-0.5f,-0.5f };
	aabb[0].max = { 0.0f,0.0f,0.0f };
	aabb[1].min = { 0.2f,0.2f,0.2f };
	aabb[1].max = { 1.0f,1.0f,1.0f };
	int AABBColor = 0;
	static bool isDebugCamera = false;

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

		/*Vector3 start = Transform(Transform(segment.origin, ViewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), ViewProjectionMatrix), viewportMatrix);
		Vector3 start2 = Transform(Transform(segment2.origin, ViewProjectionMatrix), viewportMatrix);
		Vector3 end2 = Transform(Transform(Add(segment2.origin, segment2.diff), ViewProjectionMatrix), viewportMatrix);*/
		if (IsCollision(aabb[0], aabb[1])) {
			AABBColor = RED;
		}
		else
		{
			AABBColor = WHITE;
		}
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
		ImGui::DragFloat3("AABB1:MIN", &aabb[0].min.x, 0.01f);
		ImGui::DragFloat3("AABB1:MAX", &aabb[0].max.x, 0.01f);
		ImGui::DragFloat3("AABB2:MIN", &aabb[1].min.x, 0.01f);
		ImGui::DragFloat3("AABB2:MAX", &aabb[1].max.x, 0.01f);
		ImGui::End();
		for (int i = 0; i < 2; ++i) {
			DrawAABB(aabb[i], ViewProjectionMatrix, viewportMatrix, AABBColor);
		}
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