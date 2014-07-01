#pragma once

#include "../Windows/Base.h"

#include "../Math/Vec3.h"
#include "../Math/Matrix.h"

namespace EDX
{
	class Camera
	{
	public:
		// Camera parameters
		Vector3 mPos;
		Vector3 mTarget;
		Vector3 mUp;
		Vector3 mDir;

		// First person movement params
		float mMoveScaler;
		float mRotateScaler;
		float mYaw, mPitch;

		float mFOV;
		float mRatio;
		float mNearClip;
		float mFarClip;

		float mImagePlaneDist;

	protected:
		float mFOV_2;

		// Screen resolution
		int mFilmResX;
		int mFilmResY;

		// Matrices
		Matrix mView;
		Matrix mViewInv;

		Matrix mProj;

		Matrix mScreenToRaster;
		Matrix mRasterToCamera;
		Matrix mCameraToRaster;
		Matrix mRasterToWorld;
		Matrix mWorldToRaster;

		// User input
		Vector3 mDirKB;

	public:
		Camera();
		Camera(const Vector3& ptPos, const Vector3& ptTar, const Vector3& vUp, int iResX, int iResY,
			float fFOV = 35.0f, float fNear = 0.1f, float fFar = 1000.0f);

		virtual ~Camera(void)
		{
		}

		void Init(const Vector3& ptPos, const Vector3& ptTar, const Vector3& vUp, int iResX, int iResY,
			float fFOV = 35.0f, float fNear = 0.1f, float fFar = 1000.0f);

		// Handling the resize event
		void Resize(int iWidth, int iHeight);

		// Getters
		const Matrix& GetViewMatrix() const { return mView; }
		const Matrix& GetViewInvMatrix() const { return mViewInv; }
		const Matrix& GetProjMatrix() const { return mProj; }
		const Matrix& GetRasterMatrix() const { return mScreenToRaster; }

		// Hanlding the first person movement msg
		bool HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void Transform();

		// Given a point in world space, return the raster coordinate
		inline Vector3 WorldToRaster(const Vector3 ptWorld) const { return Matrix::TransformPoint(ptWorld, mWorldToRaster); }
		inline Vector3 RasterToWorld(const Vector3 ptRas) const { return Matrix::TransformPoint(ptRas, mRasterToWorld); }
		inline Vector3 RasterToCamera(const Vector3 ptRas) const { return Matrix::TransformPoint(ptRas, mRasterToCamera); }
		inline Vector3 CameraToRaster(const Vector3 ptCam) const { return Matrix::TransformPoint(ptCam, mCameraToRaster); }
		inline bool CheckRaster(const Vector3& ptRas) const { return ptRas.x < float(mFilmResX) && ptRas.x >= 0.0f && ptRas.y < float(mFilmResY) && ptRas.y >= 0.0f; }
	};
}