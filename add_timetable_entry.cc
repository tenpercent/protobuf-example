#include <iostream>
#include <fstream>
#include <string>
#include "timetable.pb.h"

// This function fills in a Person message based on user input.
void PromptForNewEntry(timetable::TimeTable_TimeTableEntry* timetable_line) {
  ::std::cout << "Adding new timetable entry!" << ::std::endl;
  
  ::std::cout << "Enter group number: ";
  int gnumber_;
  ::std::cin >> gnumber_;
  timetable_line->set_groupnumber(gnumber_);
  ::std::cin.ignore(256, '\n');

  ::std::cout << "Enter room number: ";
  int roomNumber_;
  ::std::cin >> roomNumber_;
  timetable_line->set_roomnumber(roomNumber_);
  ::std::cin.ignore(256, '\n');

  ::std::cout << "Enter professor name: ";
  ::std::string professorName_;
  getline(::std::cin, professorName_);
  timetable_line->set_professor(professorName_);

  ::std::cout << "Enter subject: ";
  ::std::string subj_repr;
  getline(::std::cin, subj_repr);
  timetable::TimeTable_Subject subj_;
  if (!(TimeTable_Subject_Parse(
    subj_repr, &subj_))) {
		::std::cout << "Failed to parse subject from input";
  } else {
  	timetable_line->set_subject(subj_);
  }
  
  ::std::cout << "Enter date (required format is WWW HH:MM where WWW is the day of week, HH is the hour and MM is the minute): ";
  ::std::string time_repr;
  getline(::std::cin, time_repr);
  timetable::TimeTable_TimeStruct *time_ = new timetable::TimeTable_TimeStruct();
  int hour, minute;
  timetable::TimeTable_DayOfWeek dow;
  auto hour_s = time_repr.substr(4, 2);
  auto minute_s = time_repr.substr(7, 2);
  auto dow_s = time_repr.substr(0, 3);
  hour = (hour_s[0] - '0') * 10 + hour_s[1] - '0';
  minute = (minute_s[0] - '0') * 10 + minute_s[1] - '0';
  std::transform(dow_s.begin(), dow_s.end(), dow_s.begin(), ::toupper);
  if (!TimeTable_DayOfWeek_Parse(
	  dow_s, &dow)) {
	::std::cout << "Failed to parse day of week from input";	
  } else {
	time_->set_dayofweek(dow);
  }
  time_->set_hour(hour);
  time_->set_minute(minute);
  timetable_line->set_allocated_time(time_);
  
  ::std::cout << "Done!" << ::std::endl;
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    ::std::cerr << "Usage:  " << argv[0] << " TIMETABLE_FILE" << ::std::endl;
    return -1;
  }

  timetable::TimeTable time_table;

  {
    // Read the existing address book.
    ::std::fstream input(argv[1], ::std::ios::in | ::std::ios::binary);
    if (!input) {
      ::std::cout << argv[1] << ": File not found.  Creating a new file." << ::std::endl;
    } else if (!time_table.ParseFromIstream(&input)) {
      ::std::cerr << "Failed to parse address book." << ::std::endl;
      return -1;
    }
  }

  // Add an address.
  PromptForNewEntry(time_table.add_ttentry());

  {
    // Write the new address book back to disk.
    ::std::fstream output(argv[1], ::std::ios::out | ::std::ios::trunc | ::std::ios::binary);
    if (!time_table.SerializeToOstream(&output)) {
      ::std::cerr << "Failed to write address book." << ::std::endl;
      return -1;
    }
  }

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
