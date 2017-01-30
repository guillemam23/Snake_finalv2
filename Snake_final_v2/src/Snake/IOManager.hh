#pragma once
#include "ID.hh"
#include <fstream>
#include <sstream>
#include <iterator>
//#include "Logger.hh"
#include "Assert.hh"
#include "Resource.hh"
#include <XML/rapidxml_utils.hpp>
//using namespace Logger;
#include <string>
#include <iostream>
#include "LevelScene.hh"
#include "Score.hh"
#include "RankingScene.hh"
#include "SceneManager.hh"
using namespace std;
//Load XML

namespace IOManager {

	static  std::vector<std::vector<ObjectID>>  XMLLevel(std::string &&filename, int &lvl_select, int &rows, int &cols,
		int &temp, float &vel, int &alimx, int &alimy) {
		cout << "lvl" << lvl_select << endl;
		rapidxml::file<> xmlFile(RESOURCE_FILE(filename));
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *root_node = doc.first_node("document");

		if (lvl_select == 1) {
			rapidxml::xml_node<> * node = root_node->first_node("level1");

			rows = atoi(node->first_node("rows")->value());
			cols = atoi(node->first_node("cols")->value());
			temp = atoi(node->first_node("temp")->value());
			vel = atof(node->first_node("vel")->value());
			alimx = atoi(node->first_node("alimx")->value());
			alimy = atoi(node->first_node("alimy")->value());

		}
		if (lvl_select == 2) {
			rapidxml::xml_node<> * node = root_node->first_node("level2");

			rows = atoi(node->first_node("rows")->value());
			cols = atoi(node->first_node("cols")->value());
			temp = atoi(node->first_node("temp")->value());
			vel = atof(node->first_node("vel")->value());
			alimx = atoi(node->first_node("alimx")->value());
			alimy = atoi(node->first_node("alimy")->value());

		}
		if (lvl_select == 3) {
			rapidxml::xml_node<> * node = root_node->first_node("level3");

			rows = atoi(node->first_node("rows")->value());
			cols = atoi(node->first_node("cols")->value());
			temp = atoi(node->first_node("temp")->value());
			vel = atof(node->first_node("vel")->value());
			alimx = atoi(node->first_node("alimx")->value());
			alimy = atoi(node->first_node("alimy")->value());

		}

		rows = rows * 13;
		cols = cols * 13;
		temp = temp * 10.;
		vel = vel * 5;
		alimx = alimx * 6;
		alimy = alimy * 2;

		std::vector<std::vector<ObjectID>> lvlData = std::vector<std::vector<ObjectID>>(rows, vector <ObjectID>(cols));
		return lvlData;
	}

	void SaveRanking(Score newscore);
	
	void BubbleSort(Score rank[], int lenght);
	
	void LoadRanking();
	

}

