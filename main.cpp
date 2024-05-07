#include <Novice.h>
#include"mathMT-Git.h"
#include<cstdint>

const char kWindowTitle[] = "GC2B_12_ナカムラ_アヤネ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//画面の大きさ
	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//クロス積
	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Cross(v1, v2);
	//入力
	Vector3 rotate{};
	Vector3 translate{};
	//よくわからん
	Vector3 cameraPosition{};

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
		//前
		if (keys[DIK_S])
		{
			translate.z += 0.5f;
		}
		//後ろ
		if (keys[DIK_W])
		{
			translate.z -= 0.5f;
		}
		//右
		if (keys[DIK_D])
		{
			translate.x += 0.5f;
		}
		//左
		if (keys[DIK_A])
		{
			translate.x += 0.5f;
		}
		//図形回転
		rotate.y -= 0.1f;
		//各種行列の計算
		Matrix4x4 woldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth)/float(kWindowHeight),0.1f,100.0f);
		Matrix4x4 worldViewProjectionMatrix=Multiply(woldMatrix,Multiply(viewMatrix,projectionMatrix));
		Matrix4x4 viewportMatrix=MakeViewportMatirix(0,0,float(kWindowWidth),float(kWindowHeight),0.0f,1.0f);
		Vector3 screenVertices[3]={};
		for(uint32_t i=0;i<3;++i)
		{
		Vector3 ndcVertex=Transform(kLocal)
		}

			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///

			VectorScreenPrintf(0, 0, cross, "Cross");

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
