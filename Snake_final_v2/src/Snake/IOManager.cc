#include"IOManager.hh"

void IOManager::SaveRanking(Score newscore)
{
	LoadRanking();

	if (SM.GetScene<RankingScene>()->ranking[0].score < newscore.score) {

		SM.GetScene<RankingScene>()->ranking[0].score = newscore.score;
		SM.GetScene<RankingScene>()->ranking[0].name = newscore.name;
	}

	//Ordenar el ranking

	BubbleSort(SM.GetScene<RankingScene>()->ranking, 10);

	std::ofstream fsalida;

	if (SM.GetScene<LevelScene>()->m_lvl == 1) {
		fsalida.open(RESOURCE_FILE(std::string("cfg/EasyRanking.dat")), std::ios::out | std::ios::binary);
	}
	if (SM.GetScene<LevelScene>()->m_lvl == 2) {
		fsalida.open(RESOURCE_FILE(std::string("cfg/MediumRanking.dat")), std::ios::out | std::ios::binary);
	}	
	if (SM.GetScene<LevelScene>()->m_lvl == 3) {
		fsalida.open(RESOURCE_FILE(std::string("cfg/HardRanking.dat")), std::ios::out | std::ios::binary);
	}
	fsalida.write(reinterpret_cast<char*>(&SM.GetScene<RankingScene>()->ranking), sizeof(SM.GetScene<RankingScene>()->ranking));
	fsalida.close();

	for (int i = 0; i < 10; i++) {
		std::cout << " i: " << i << " Name: " << SM.GetScene<RankingScene>()->ranking[i].name << "  score: " << SM.GetScene<RankingScene>()->ranking[i].score << std::endl;
	}
}

void IOManager::BubbleSort(Score rank[], int lenght)
{
	Score temp;
	for (int i = 1; i < lenght; ++i) {
		for (int j = 0; j < (lenght - i); ++j) {
			if (rank[j].score > rank[j + 1].score) {
				temp = rank[j];
				rank[j] = rank[j + 1];
				rank[j + 1] = temp;
			}
		}
	}
}

void IOManager::LoadRanking()
{
	//Carregar el document

	std::ifstream fentrada;
	if (SM.GetScene<LevelScene>()->m_lvl == 1) {
		fentrada.open(RESOURCE_FILE(std::string("cfg/EasyRanking.dat")), std::ios::in | std::ios::binary);
	}
	if (SM.GetScene<LevelScene>()->m_lvl == 2) {
		fentrada.open(RESOURCE_FILE(std::string("cfg/MediumRanking.dat")), std::ios::in | std::ios::binary);
	}
	if (SM.GetScene<LevelScene>()->m_lvl == 3) {
		fentrada.open(RESOURCE_FILE(std::string("cfg/HardRanking.dat")), std::ios::in | std::ios::binary);
	}
	//Llegir el document

	fentrada.read(reinterpret_cast<char*>(&SM.GetScene<RankingScene>()->ranking), sizeof(SM.GetScene<RankingScene>()->ranking));

	//Tancar i sincronitzar ranking

	fentrada.close();
}