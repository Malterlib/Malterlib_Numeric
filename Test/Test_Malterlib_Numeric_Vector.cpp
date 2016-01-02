// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Numeric/Vector>

NMib::NMath::CVecAggr2Dfp32 g_TestAggreate2D = {0.0f, 1.0f};
NMib::NMath::CVecAggr3Dfp32 g_TestAggreate3D = {0.0f, 1.0f, 2.0f};
NMib::NMath::CVecAggr4Dfp32 g_TestAggreate4D = {0.0f, 1.0f, 2.0f, 3.0f};


#if 0
class CTestVector : public CMalterlibTest
{
public:


	NMib::NStr::CStr Certify(CTestInterface &_Interface)
	{

#if 0
		static NMib::NMath::CVec3Dfp32 Test;
		static NMib::NMath::CVec3Dfp32 Test1(0.0f);
		static NMib::NMath::CVec3Dfp32 Test2(0.0f, 1.0f, 2.0f);
		static NMib::NMath::CVec3Dfp32 Test3(g_TestAggreate3D);
		static NMib::NMath::CVec3Dfp32 Test4(Test2);

		static NMib::NMath::CVec4Dfp32 Test5(0.0f, 1.0f, 2.0f, 3.0f);

		static NMib::NMath::CVec4Dfp32 Test6(Test5);

		static NMib::NMath::CVec4Dfp32 Test7(DMibVec4Dfp32FixedPointConst(3,141592653589793238,0, 1,5,0, 2,5,-30, 3,5,2));

		NMib::NMath::CVecAggr4x4fp32 Matrix0;
		Matrix0[0] = NMib::NMath::CVec4Dfp32(1.0f, 0.0f, 0.0f, 20.0f);
		Matrix0[1] = NMib::NMath::CVec4Dfp32(0.0f, 1.0f, 0.0f, 20.0f);
		Matrix0[2] = NMib::NMath::CVec4Dfp32(0.0f, 0.0f, 1.0f, 20.0f);
		Matrix0[3] = NMib::NMath::CVec4Dfp32(0.0f, 0.0f, 0.0f, 0.0f);

		NMib::NMath::CVecAggr4x4fp32 Matrix1;
		Matrix1[0] = NMib::NMath::CVec4Dfp32(1.0f, 0.0f, 0.0f, 10.0f);
		Matrix1[1] = NMib::NMath::CVec4Dfp32(0.0f, 1.0f, 0.0f, 10.0f);
		Matrix1[2] = NMib::NMath::CVec4Dfp32(0.0f, 0.0f, 1.0f, 10.0f);
		Matrix1[3] = NMib::NMath::CVec4Dfp32(0.0f, 0.0f, 0.0f, 0.0f);

		static NMib::NMath::CVecAggr4x4fp32 Matrix2 = Matrix0 * Matrix1;


		NMib::NMath::CVecAggr3x4fp32 Matrix4;
		Matrix4[0] = NMib::NMath::CVec4Dfp32(1.0f, 0.0f, 0.0f, 25.0f);
		Matrix4[1] = NMib::NMath::CVec4Dfp32(0.0f, 1.0f, 0.0f, 25.0f);
		Matrix4[2] = NMib::NMath::CVec4Dfp32(0.0f, 0.0f, 1.0f, 25.0f);

		static NMib::NMath::CVecAggr4x4fp32 Matrix3 = Matrix0 * Matrix4;
#endif

		return "";
	}
};

DMibRuntimeClass(CMalterlibTest, CTestVector);

#endif
