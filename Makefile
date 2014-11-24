PROTOBUF_J_DIR=/Users/tenpercent/protobuf/java/target/classes

all: protobuf_sources writer reader
protobuf_sources: timetable.proto
	protoc --cpp_out=. timetable.proto
	protoc -I=. --java_out=. ./timetable.proto
	
writer: add_timetable_entry.cc
	c++ add_timetable_entry.cc timetable.pb.cc -I/Users/tenpercent/local/include -L/Users/tenpercent/local/lib -lprotobuf -std=c++11 -o add_timetable_entry.exe
compile_reader: ListTimeTableEntries.java
	javac -cp $PROTOBUF_J_DIR com/example/timetable/TimeTableProtos.java ListTimeTableEntries.java 
reader: compile_reader
	echo "Writing shortcut script..."
	echo '#! /bin/sh' > reader.exe
	echo 'java -classpath .:$$CLASSPATH:$$PROTOBUF_J_DIR ListTimeTableEntries "$$@"' >> reader.exe
	chmod +x reader.exe
clean:
	rm timetable.pb.cc timetable.pb.h 2&>1>/dev/null
	rm -r com 2&>1>/dev/null
	rm *.exe 2&>1>/dev/null