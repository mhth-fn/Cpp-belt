#include <string>

struct Specialization{
	std::string value;
	explicit Specialization(const std::string& new_value){
		value = new_value;
	}
};

struct Course{
	std::string value;
	explicit Course(const std::string& new_value){
		value = new_value;
	}
};

struct Week{
	std::string value;
	explicit Week(const std::string& new_value){
		value = new_value;
	}
};

struct LectureTitle {
	std::string specialization;
	std::string course;
	std::string week;
	LectureTitle(Specialization new_spec, Course new_cour, Week new_week){
		specialization = new_spec.value;
		course = new_cour.value;
		week = new_week.value;
	}
};

