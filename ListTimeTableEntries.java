import com.example.timetable.TimeTableProtos.TimeTable;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;

class ListTimeTableEntries {
  static void Print(TimeTable timetable) {
	String formatString = "%15s ; %15s ; %20s ; %20s ; %15s%n"; 
	System.out.format(formatString,
		              "Group number",
					  "Date",
					  "Subject",
					  "Professor",
					  "Room number");
    for (TimeTable.TimeTableEntry ttentry: timetable.getTtentryList()) {
	  System.out.format(formatString, 
		                ttentry.getGroupNumber(), 
						ttentry.getTime().getDayOfWeek() + " " + ttentry.getTime().getHour() + ":" + ttentry.getTime().getMinute(),
						ttentry.getSubject(),
					    ttentry.getProfessor(),
						ttentry.getRoomNumber());
    }
  }

  public static void main(String[] args) throws Exception {
    if (args.length != 1) {
      System.err.println("Usage:  ./reader.exe <filename>");
      System.exit(-1);
    }

    TimeTable entries =
      TimeTable.parseFrom(new FileInputStream(args[0]));

    Print(entries);
  }
}
