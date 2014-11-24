PROTOBUF_J_DIR=/Users/tenpercent/protobuf/java/target/classes

all: protobuf_sources add_entry.exe reader.exe

protobuf_sources: cpp java

cpp: timetable.proto
	protoc -I=. --cpp_out=. $<

java: timetable.proto
	protoc -I=. --java_out=. $<

add_entry.exe: add_timetable_entry.cc timetable.pb.cc
	@c++ $^ \
	-I/Users/tenpercent/local/include \
	-L/Users/tenpercent/local/lib \
	-lprotobuf \
	-Wall -std=c++11 \
	-o $@
	@echo 'compiled $@'

ListTimeTableEntries.class: ListTimeTableEntries.java com/example/timetable/TimeTableProtos.java
	@javac -cp $(PROTOBUF_J_DIR) $^
	@echo 'compiled $@'

reader.exe: ListTimeTableEntries.class
	@echo '#! /bin/sh' > $@
	@echo 'java -cp .:$$CLASSPATH:$(PROTOBUF_J_DIR) ListTimeTableEntries "$$@"' >> $@
	@chmod +x $@
	@echo 'created shortcut script $@'

clean:
	@echo 'cleaning up...'
	@rm timetable.pb.cc timetable.pb.h 2>&1 > /dev/null
	@rm -r com 2>&1 > /dev/null
	@rm *.exe 2>&1 > /dev/null
	@rm *.class
