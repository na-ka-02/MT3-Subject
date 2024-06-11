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

	//クロス積
	//Vector3 v1{ 1.2f,-3.9f,2.5f };
	//Vector3 v2{ 2.8f,0.4f,-1.3f };
	//Vector3 cross = Cross(v1, v2);
	////入力
	Vector3 rotate{};
	Vector3 translate{};
	//カメラポジション
	Vector3 cameraPosition{0.0f,0.4f,-7.0f};
	//カメラの位置
	Vector3 cameraTranslate{ 0.0f,2.9f,-6.49f };
	//カメラの角度
	Vector3 cameraRotate{ 0.26f,0.6f,0.0f };
	//球体
	Sphere sphere{ {0,0,0},0.5f };



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

		//入力
		// 画面を1とするから、数図でかすぎたら行き過ぎてしまう
		// ので、0.05とか小さい値にすること
		//前
		if (keys[DIK_S])
		{
			translate.z -= 0.05f;
		}
		//後ろ
		if (keys[DIK_W])
		{
			translate.z += 0.05f;
		}
		//右
		if (keys[DIK_D])
		{
			translate.x += 0.05f;
		}
		//左
		if (keys[DIK_A])
		{
			translate.x -= 0.05f;
		}
		//図形回転
		rotate.y -= 0.1f;

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("ShereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
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
		Matrix4x4 viewProjectionMatrix=Multiply(viewMatrix,projectionMatrix);
		//見た目変更座標変換
		Matrix4x4 worldViewProjectionMatrix = Multiply(woldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ビューポート座標変換
		Matrix4x4 viewportMatrix = MakeViewportMatirix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		//スクリーンに映す座標
		//Vector3 screenVertices[3] = {};
		////表示する三角形のx軸,y軸,z軸の位置
		//Vector3 kLocalVertices[3]={{0.0f,0.5f,0.0f},{0.5f,-0.5f,0.0f},{-0.5f,-0.5f,0.0f}};
		////表示する三角形の座標変換
		//for (uint32_t i = 0; i < 3;++i)
		//{
		//	Vector3 ndcVertex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
		//	screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		//}

		///
		/// ↑更新処理ここまで
		///


		//グリッド
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		//球体
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix,BLACK);

		


		///
		/// ↓描画処理ここから
		///

		/*VectorScreenPrintf(0, 0, cross, "Cross");
		Novice::DrawTriangle
	   (int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[1].x), int(screenVertices[1].y),
		int(screenVertices[2].x), int(screenVertices[2].y),
		RED, kFillModeSolid);*/

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
