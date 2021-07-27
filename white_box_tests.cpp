//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Martin Pentrak <xpentr00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Martin Pentrak
 * 
 * @brief Implementace testu prace s maticemi.
 */
 
#include "gtest/gtest.h"
#include "white_box_code.h"
#include <vector>
#include <math.h>

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

using namespace std;
class Matrix_1X1 : public ::testing::Test
{
protected:
	void SetUp() 
	{
		matrix = Matrix();
	}

	Matrix matrix;
};

class Matrix_MxN : public ::testing::Test
{
protected:

	Matrix matrix;
};




TEST_F(Matrix_1X1,constructor)
{
	EXPECT_NO_THROW(SetUp());
}
TEST_F(Matrix_1X1, set)
{
	EXPECT_TRUE(matrix.set(0,0,100));
	EXPECT_TRUE(matrix.set(0, 0, 100.2));
	EXPECT_TRUE(matrix.set(0, 0, -100));
	EXPECT_TRUE(matrix.set(0, 0, -100.2));

	EXPECT_FALSE(matrix.set(0, 1, 0));
	EXPECT_FALSE(matrix.set(1, 0, 0));
	EXPECT_FALSE(matrix.set(0, 1, 1));
	EXPECT_FALSE(matrix.set(1,1,1));
}

TEST_F(Matrix_1X1, get)
{
	EXPECT_NO_THROW(matrix.get(0, 0));

	EXPECT_ANY_THROW(matrix.get(1, 0));
	EXPECT_ANY_THROW(matrix.get(0, -1));
	EXPECT_ANY_THROW(matrix.get(-1, 0));
	EXPECT_ANY_THROW(matrix.get(0, 1000));
	EXPECT_ANY_THROW(matrix.get(1, -100));
}

TEST_F(Matrix_MxN, constructor)
{
	EXPECT_NO_THROW(matrix = Matrix(2,2));
	EXPECT_NO_THROW(matrix = Matrix(4, 4));
	EXPECT_NO_THROW(matrix = Matrix(3, 4));
	EXPECT_NO_THROW(matrix = Matrix(4, 3));

	EXPECT_ANY_THROW(matrix = Matrix(-4, 3));
	EXPECT_ANY_THROW(matrix = Matrix(4, -3));
	EXPECT_ANY_THROW(matrix = Matrix(0, 0));
	EXPECT_ANY_THROW(matrix = Matrix(-5000, 3));	
}
TEST_F(Matrix_MxN, set)
{
	matrix = Matrix(2, 2);

	EXPECT_TRUE(matrix.set(0, 1, 100));
	EXPECT_TRUE(matrix.set(1, 0, -200));
	EXPECT_TRUE(matrix.set(0, 0, 1));
	
	EXPECT_FALSE(matrix.set(0, -1, 0));
	EXPECT_FALSE(matrix.set(-1, 0, 0));
	EXPECT_FALSE(matrix.set(0, 2, 1));
	EXPECT_FALSE(matrix.set(2, 1, 1));

	matrix = Matrix(3, 4);

	EXPECT_TRUE(matrix.set(0, 3, 100));
	EXPECT_TRUE(matrix.set(2, 0, -200));
	EXPECT_TRUE(matrix.set(0, 0, 1));

	EXPECT_FALSE(matrix.set(3,2, 0));
	EXPECT_FALSE(matrix.set(-1, 0, 0));
	EXPECT_FALSE(matrix.set(0, 4, 1));
	EXPECT_FALSE(matrix.set(3, 1, 1));

	matrix = Matrix(4, 3);
	EXPECT_TRUE(matrix.set(3, 2, 100));
	EXPECT_TRUE(matrix.set(2, 2, -200));
	EXPECT_TRUE(matrix.set(1, 2, 1));

	EXPECT_FALSE(matrix.set(2, 3, 0));
	EXPECT_FALSE(matrix.set(-1, 0, 0));
	EXPECT_FALSE(matrix.set(1, 3, 1));
}

TEST_F(Matrix_MxN, set2)
{
	matrix = Matrix(2, 2);
	Matrix matrix1= Matrix(2, 2);
	Matrix matrix2= Matrix(3,3);
	
	EXPECT_TRUE(matrix.set({
		{5,-5},
		{-1000,1000},
	}));

	EXPECT_FALSE(matrix1.set({
		{5, -5},
		{ -1000,1000 },
		{ 5, -5 },
		{ -1000,1000 },
	}));
	//EXPECT_DEATH(matrix1.set({ {5,5} }),  "Assertion failed: vector subscript out of range");
}

TEST_F(Matrix_MxN, get)
{
	matrix = Matrix(2, 2);
	matrix.set({
		{5,-5},
		{-1000,1000},
		});
	EXPECT_TRUE(matrix.get(0, 1));
	EXPECT_ANY_THROW(matrix.get(1, 2));
	EXPECT_ANY_THROW(matrix.get(2, 1));
}

TEST_F(Matrix_MxN, equal)
{
	matrix = Matrix(2, 2);
	matrix.set({
		{5,-5},
		{-1000,1000},
		});
	Matrix matrix1 = Matrix(2, 2);
	matrix1.set({
		{5,-5},
		{-1000,1000},
		});
	Matrix matrix2 = Matrix(3, 3);
	matrix2.set({
		{5,-5},
		{-1000,1000},
		{-1000,1000},
		});
	EXPECT_ANY_THROW(matrix1 == matrix2);
	matrix2 = Matrix(2, 3);
	EXPECT_ANY_THROW(matrix1 == matrix2);
	EXPECT_TRUE(matrix == matrix1);
	matrix1.set({
	{5,5},
	{-1000,1000},
		});
	EXPECT_FALSE(matrix == matrix1);
	matrix1.set({
	{5,-5},
	{1000,1000},
		});
	EXPECT_FALSE(matrix == matrix1);
}

TEST_F(Matrix_MxN, plus)
{
	matrix = Matrix(2, 2);
	matrix.set({
		{5,-5},
		{-1000,1000},
		});
	Matrix matrix1 = Matrix(2, 2);
	matrix1.set({
		{5,-5},
		{-1000,500},
		});
	Matrix matrix2 = Matrix(3, 3);
	matrix2.set({
		{5,-5,5},
		{-1000,1000,5},
		{-1000,1000,5},
		});
	EXPECT_ANY_THROW(matrix1 + matrix2);
	matrix2 = Matrix(2, 3);
	EXPECT_ANY_THROW(matrix1 + matrix2);
	EXPECT_NO_THROW(matrix + matrix1);
}
TEST_F(Matrix_MxN, multiply)
{
	matrix = Matrix(2, 2);
	matrix.set({
		{5,-5},
		{-1000,1000},
		});
	Matrix matrix1 = Matrix(1, 2);
	matrix1.set({
		{5,-5},

		});
	Matrix matrix2 = Matrix(2, 3);
	matrix2.set({
		{5,-5,1},
		{-1000,1000,1},
		});

	EXPECT_NO_THROW(matrix*matrix2);
	EXPECT_ANY_THROW(matrix*matrix1);
	EXPECT_NO_THROW(matrix * 2);
}
TEST_F(Matrix_MxN, equation)
{
	matrix = Matrix(3, 3);
	matrix.set({
		{5,-5,1},
		{1000,1000,1},
		{1000,1000,1},
		});
	Matrix matrix2 = Matrix(2, 3);
	matrix2.set({
		{5,-5,1},
		{-1000,1000,1},
		});
	Matrix matrix3 = Matrix();
	matrix3.set({ { 1 } });
	Matrix matrix4 = Matrix(2, 2);
	matrix4.set({
		{5,5},
		{-1000,1000},

		});
	EXPECT_ANY_THROW(matrix.solveEquation({5,-5}));        // pocet prvkov != pocet riadkov
	EXPECT_ANY_THROW(matrix2.solveEquation({ 5,-5,5 }));   // !stvorcova matica
	EXPECT_ANY_THROW(matrix.solveEquation({ 5,-5,5 }));    // singularna maticca
	EXPECT_NO_THROW(matrix3.solveEquation({ 2 }));         // matica 1*1 
	EXPECT_NO_THROW(matrix4.solveEquation({ 2,3 }));       // matica 2*2
	matrix.set({										   // nastavenie matice tak aby nebola singularna						
		{1,2,3},
		{2,-1,1},
		{3,1,-1},
		});
	EXPECT_NO_THROW(matrix.solveEquation({ 1,1,1 }));      // matica 3*3
}
TEST_F(Matrix_MxN,transpose)
{
	matrix = Matrix(3, 3);
	matrix.set({
		{5,-5,1},
		{1000,1000,1},
		{1000,1000,1},
		});
	Matrix matrix2 = Matrix(2, 3);
	matrix2.set({
		{5,-5,1},
		{-1000,1000,1},
		});
	EXPECT_NO_THROW(matrix.transpose());
	EXPECT_NO_THROW(matrix2.transpose());
}
TEST_F(Matrix_MxN, inverse)
{
	matrix = Matrix(3, 3);
	matrix.set({
		{5,-5,1},
		{1000,1000,1},
		{1000,1000,1},
		});
	Matrix matrix2 = Matrix(2, 3);
	matrix2.set({
		{5,-5,1},
		{-1000,1000,1},
		});
	Matrix matrix3 = Matrix();
	matrix3.set({ { 1 } });
	Matrix matrix4 = Matrix(2, 2);
	matrix4.set({
		{5,5},
		{-1000,1000},

		});
	EXPECT_ANY_THROW(matrix2.inverse());
	EXPECT_ANY_THROW(matrix3.inverse());
	EXPECT_ANY_THROW(matrix.inverse());
	matrix.set({										   // nastavenie matice tak aby nebola singularna						
	{1,2,3},
	{2,-1,1},
	{3,1,-1},
		});
	EXPECT_NO_THROW(matrix.inverse());
	EXPECT_NO_THROW(matrix4.inverse());
}

	






/*** Konec souboru white_box_tests.cpp ***/
