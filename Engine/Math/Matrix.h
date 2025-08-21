#pragma once

#include "Vector2.h"
#include "Vector4.hpp"

namespace Engine
{
	namespace Math
	{
		class Matrix;
		//create an alias for cache alignment
		typedef __declspec(align(64)) Matrix FastMatrix;

		class Matrix
		{
			friend Vector4 operator*(const Vector4 & i_vec, const Matrix & i_mtx);

		public:
			Matrix();

			Matrix(
				float i_11, float i_12, float i_13, float i_14,
				float i_21, float i_22, float i_23, float i_24,
				float i_31, float i_32, float i_33, float i_34,
				float i_41, float i_42, float i_43, float i_44 );

			//Copy constructor & assigment operator
			Matrix( const Matrix & i_other );
			Matrix & operator=( const Matrix & i_other );

			//Useful matrix creators
			static Matrix CreateIdentity( void );
			static Matrix CreateXRotation( float i_RotationRadians );
			static Matrix CreateYRotation( float i_RotationRadians );
			static Matrix CreateZRotation( float i_RotationRadians );

			static Matrix CreateTranslation( Vector2 i_trans );
			static Matrix CreateTranslation( float i_transX, float i_transY );
			static Matrix CreateScale( float i_scaleX, float i_scaleY );

			//Invert this instance
			void Invert( void );
			//Return a matrix that is the inverse of this instance but don't modify this instance
			Matrix GetInverse( void ) ;

			//Transpose this instance
			void Transpose( void );
			//return a matrix that is the transpose of this instance but don't modify this instance
			Matrix GetTranspose( void ) const;

			//Multiply Matrix * Matrix
			//return *this * i_other
			Matrix operator*( const Matrix & i_other ) const;

			//Multiply Vector by Matrix
			//return v * M
			Vector4 MultiplyLeft( const Vector4 & i_Vector ) const;

			bool operator==( const Matrix & i_other ) const;

			static const FastMatrix Identity;

		private:
			float
				//m_<row><column>
				m_11, m_12, m_13, m_14,	//row 1
				m_21, m_22, m_23, m_24,	//row 2
				m_31, m_32, m_33, m_34,	//row 3
				m_41, m_42, m_43, m_44;	//row4

			//Matrix Multiply( const Matrix & i_other, Matrix & o_out ) const;

			float Determinant();

			//internal inverse function used by Invert() and GetInverse()
			//Matrix & InverseSSE( Matrix & o_out ) const;
			//Matrix & MultiplySSE( const Matrix & i_other, Matrix & o_out ) const;
		};

		//Allows us to use V = V * M; (i.e. row vector)
		inline Vector4 operator*( const Vector4 & i_vec, const Matrix & i_mtx );

	}	//namespace Math
}	//namespace Engine

#include "Matrix-inl.h"