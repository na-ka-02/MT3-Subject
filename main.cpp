#include <Novice.h>
#include"mathMT-Git.h"
#include<cstdint>
#include<imgui.h>
#include"Sphere.h"

const char kWindowTitle[] = "GC2B_12_ナカムラ_アヤネ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//画面の大きさ
	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	////入力
	Vector3 rotate{};
	Vector3 translate{};
	//カメラポジション
	Vector3 cameraPosition{ 0.0f,0.4f,-7.0f };
	//カメラの位置
	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	//カメラの角度
	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };
	//球体1
	Sphere sphere1{ {0,0,0},0.5f };
	//球体2
	Sphere sphere2{ {0,0,0.7f},0.5f };

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };
	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = Project(Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);


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

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("ShereCenter", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere1.radius, 0.01f);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		//各種行列の計算
		//ワールド座標変換
		Matrix4x4 woldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		//カメラ座標変換
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		//ビュー座標変換
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		//透視投影座標変換
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//ビュープロジェクション
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		//見た目変更座標変換
		Matrix4x4 worldViewProjectionMatrix = Multiply(woldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ビューポート座標変換
		Matrix4x4 viewportMatrix = MakeViewportMatirix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//グリッド
		DrawGrid(viewProjectionMatrix, viewportMatrix);

		//点の描画
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, WHITE);

		if(IsCollision(sphere1, sphere2)==true)
		{
			DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, RED);
		}

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
