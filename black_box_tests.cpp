//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Martin Pentrak <xpentr00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Martin Pentrak
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
using namespace std;

class EmptyTree : public ::testing::Test
{
protected:
	BinaryTree binTree = BinaryTree();
};

class NonEmptyTree : public ::testing::Test
{
protected:
	virtual void SetUp() {
		int values[] = { 10, 85, 15, 70, 20, 60, 30, 50 };

		for (int i = 0; i < 8; ++i)
			binTree.InsertNode(values[i]);
	}

	BinaryTree binTree = BinaryTree();
};

class TreeAxioms : public ::testing::Test
{
protected:
	virtual void SetUp() {
		int values[] = { 10, 85, 15, 70, 20, 60, 30, 50 };

		for (int i = 0; i < 8; ++i)
			binTree.InsertNode(values[i]);
	}
	BinaryTree binTree = BinaryTree();
};


TEST_F(EmptyTree, InsertNode)
{
	//vlozenie prveho prvku a testovanie ci sa vlozil spravne
	pair<bool, BinaryTree::Node_t *>  pair,pair2;
	
	EXPECT_TRUE(binTree.GetRoot()==NULL); //testovanie ci je strom prazdny

	EXPECT_NO_THROW(pair=binTree.InsertNode(5));
	BinaryTree::Node_t *node = pair.second;
	EXPECT_EQ(pair.first, true);
	EXPECT_EQ(node->key, 5);
	EXPECT_TRUE(node->pRight != NULL);
	EXPECT_TRUE(node->pLeft != NULL);
	EXPECT_TRUE(node->color == BLACK);
	EXPECT_TRUE(node->pParent == NULL);

	//vlozenie zaporneho cisla
	EXPECT_NO_THROW(pair=binTree.InsertNode(-5));
	EXPECT_EQ(pair.first, true);
	EXPECT_EQ(node->pLeft->key, -5);
	EXPECT_TRUE(node->pLeft->pRight != NULL);
	EXPECT_TRUE(node->pLeft->pLeft != NULL);
	EXPECT_TRUE(node->pLeft->color == RED);
	EXPECT_TRUE(node->pLeft->pParent == node);

	//opatovek vlozenie rovakej hodnoty
	EXPECT_NO_THROW(pair2 = binTree.InsertNode(5));
	EXPECT_EQ(pair2.first, false);
	EXPECT_TRUE(pair2.second == node);

	//vlozenie vacsieho cisla ako root
	EXPECT_NO_THROW(pair = binTree.InsertNode(12));
	EXPECT_EQ(pair.first, true);
	EXPECT_EQ(node->pRight->key, 12);
	EXPECT_TRUE(node->pRight->pRight != NULL);
	EXPECT_TRUE(node->pRight->pLeft != NULL);
	EXPECT_TRUE(node->pRight->color == RED);
	EXPECT_TRUE(node->pRight->pParent == node);
}

TEST_F(EmptyTree, DeleteNode)
{
	EXPECT_TRUE(binTree.GetRoot() == NULL); //testovanie ci je strom prazdny
	EXPECT_FALSE(binTree.DeleteNode(10));   //ako struktura nema root potom by tato funkcia mala vratit false
}

TEST_F(EmptyTree, FindNode)
{
	EXPECT_TRUE(binTree.GetRoot() == NULL); //testovanie ci je strom prazdny
	EXPECT_TRUE(binTree.FindNode(10)== NULL);   //ako struktura nema root potom by tato funkcia mala vratit false
}

TEST_F(NonEmptyTree, InsertNode)
{
	pair<bool, BinaryTree::Node_t *>  pair, pair2;

	EXPECT_TRUE(binTree.GetRoot() != NULL); //testovanie ci je strom prazdny
	
	EXPECT_NO_THROW(pair = binTree.InsertNode(-5));
	BinaryTree::Node_t *node = pair.second;

	EXPECT_EQ(pair.first, true);
	EXPECT_EQ(node->key, -5);
	EXPECT_TRUE(node->pRight != NULL);
	EXPECT_TRUE(node->pLeft != NULL);
	EXPECT_TRUE(node->color == RED);
	EXPECT_TRUE(node->pParent->key == 10 );
	
	//opatovek vlozenie rovakej hodnoty
	EXPECT_NO_THROW(pair = binTree.InsertNode(15));
	EXPECT_EQ(pair.first, false);
	EXPECT_TRUE(pair.second == binTree.GetRoot()->pLeft);

	//vlozenie vacsieho cisla ako root
	EXPECT_NO_THROW(pair = binTree.InsertNode(59));
	EXPECT_EQ(pair.first, true);
	EXPECT_EQ(pair.second->key, 59);
	EXPECT_TRUE(pair.second->pRight->key == 60);
	EXPECT_TRUE(pair.second->pLeft->key == 50);
	EXPECT_TRUE(pair.second->color == BLACK);
	EXPECT_TRUE(pair.second->pParent->key ==70 );
}

TEST_F(NonEmptyTree, DeleteNode)
{
	//vymazanie neexistujeceho prvku
	EXPECT_FALSE(binTree.DeleteNode(59));

	//vymazanie prvku z prava
	EXPECT_TRUE(binTree.GetRoot()->pRight->pLeft->key == 60);
	EXPECT_TRUE(binTree.DeleteNode(60));
	EXPECT_TRUE(binTree.GetRoot()->pRight->pLeft->key != 60);

	//vymazanie prvku z lava
	EXPECT_TRUE(binTree.GetRoot()->pLeft->pRight->key == 20);
	EXPECT_TRUE(binTree.DeleteNode(20));
	EXPECT_TRUE(binTree.GetRoot()->pLeft->pRight->key != 20);
	
	//vymazanie korena
	int root;
	EXPECT_TRUE(binTree.DeleteNode(root = binTree.GetRoot()->key));
	EXPECT_TRUE(binTree.GetRoot()->key != root);
}
TEST_F(NonEmptyTree, FindNode)
{
	//hladanie korena
	EXPECT_TRUE(binTree.FindNode(30) == binTree.GetRoot() );

	//hladanie prvku vlavo
	EXPECT_TRUE(binTree.FindNode(15) == binTree.GetRoot()->pLeft);

	//hladanie prvku vpravo
	EXPECT_TRUE(binTree.FindNode(70) == binTree.GetRoot()->pRight);

	//hladanie neexistujuceho prvku
	EXPECT_FALSE(binTree.FindNode(-15));
}

TEST_F(TreeAxioms, Axiom1)
{
	vector<BinaryTree::Node_t*> outLeafNodes;
	//Leafs sa nahraju do pola
	EXPECT_NO_THROW(binTree.GetLeafNodes(outLeafNodes));

	//cyklus prechadza Leafs a kontroluje farbu
	for (unsigned int i = 0; i < outLeafNodes.size(); i++)
	{
		EXPECT_TRUE(outLeafNodes[i]->color == BLACK);
	}
}
TEST_F(TreeAxioms, Axiom2)
{
	std::vector<BinaryTree::Node_t*> outAllNodes;
	EXPECT_NO_THROW(binTree.GetAllNodes(outAllNodes));

	for (unsigned int i = 0; i < outAllNodes.size(); i++)
	{
		if (outAllNodes[i]->color == RED)
		{
			EXPECT_TRUE(outAllNodes[i]->pLeft->color == BLACK);
			EXPECT_TRUE(outAllNodes[i]->pRight->color == BLACK);
		}			
	}
}

TEST_F(TreeAxioms, Axiom3)
{
	vector<BinaryTree::Node_t*> outLeafNodes;
	//Leafs sa nahraju do pola
	EXPECT_NO_THROW(binTree.GetLeafNodes(outLeafNodes));

	unsigned int nodes_n=0;
	//zisti kolko je uzlovak od lubovolneho leaf k root
	for (outLeafNodes[0]; outLeafNodes[0]->pParent != NULL; outLeafNodes[0] = outLeafNodes[0]->pParent)
	{
		if (outLeafNodes[0]->color == BLACK)
		{
			nodes_n++;
		}
	}

	// prechaze vsetky leaf uzly a ak su cierne tak kontroluje ci vsetky maju rovnaku vzdialenost k root

	for (unsigned int i = 1; i < outLeafNodes.size(); i++) //zaciname od indexu 1 lebo 0 sme prešli vyšie
	{
		int toRoot=0;
		for (outLeafNodes[i]; outLeafNodes[i]->pParent != NULL; outLeafNodes[i] = outLeafNodes[i]->pParent)
		{
			if (outLeafNodes[i]->color == BLACK)
			{
				toRoot++;
			}
		}
		EXPECT_EQ(nodes_n, toRoot);
	}	
}



