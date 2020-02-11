#include "gtest/gtest.h"
#include "dean.h"


TEST(stud, id){
	Student* stud = new Student("Arakcheev Artem", 0);
	int id = stud->getId();
	EXPECT_EQ(0, id);
}

TEST(deanery, changegroup){
	Deanery hse;
	Group* group1 = hse.createGroup("group1", "spec1");
	Group* group2 = hse.createGroup("group2", "spec2");
	hse.createStudent(0, "Ogurliev Anzor", group1);
	hse.changeGroup("Ogurliev Anzor", group1, group2);
	string name = group2->getStudents()[0]->getName();
	EXPECT_EQ("Ogurliev Anzor", name);
}

TEST(deanery, averageforstud){
	Deanery hse;
	Group* group = hse.createGroup("group", "spec");
	hse.createStudent(0, "Ogurliev Anzor", group);
	hse.addMarks(group, "Ogurliev Anzor", 4);
	hse.addMarks(group, "Ogurliev Anzor", 6);
	double mark = hse.getAverageStudent(group, "Ogurliev Anzor");
	EXPECT_EQ(5, mark);
}

TEST (deanery, compareoftitles){
	Deanery hse;
	Group* PMI = hse.createGroup("18-PMI", "Прикладная математика и информатика");
	EXPECT_EQ("18-PMI",PMI->getTitle());
}
TEST (deanery, compareofspecializations) {
	Deanery hse;
	Group* BI = hse.createGroup("18-BI", "Бизнес-информатика");
	EXPECT_EQ("Бизнес-информатика",BI->getSpec());
}

TEST (deanery, chooseofhead) {
	Deanery hse;
	ifstream inp("students.txt");
	int id = 0;
	char div = ':';
	while(!inp.eof()){
		string buf;
		getline(inp, buf, '\n');
		vector<string> data;
		string dat;
		istringstream str(buf);
		while (getline(str, dat, div))
			data.push_back(dat);
		if (data[1] == "18-PMI"){
			hse.createStudent(id, data[0], PMI);
			for (int i = 0; i < 5; i++)
				hse.addMarks(PMI, data[0], rand() % 10);
		}
		if (data[1] == "18-PI"){
			hse.createStudent(id, data[0], PI);
			for (int i = 0; i < 5; i++)
				hse.addMarks(PI, data[0], rand() % 10);
		}
		if (data[1] == "18-BI"){
			hse.createStudent(id, data[0], BI);
			for (int i = 0; i < 5; i++)
				hse.addMarks(BI, data[0], rand() % 10);
		}
		id++;
	}
	EXPECT_NE(NULL,BI->searchStudentName("Казанцев Иннокентий Алексеевич"));
}
