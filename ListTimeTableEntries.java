import com.example.timetable.TimeTableProtos.TimeTable;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;

class ListTimeTableEntries {
  static void Print(TimeTable timetable) {
	System.out.println("Group number; date; subject; professor; room number");
    for (TimeTable.TimeTableEntry ttentry: timetable.getTtentryList()) {
	  System.out.println(ttentry.getGroupNumber() + " ; " + ttentry.getTime().getDayOfWeek() + " " +
		                 ttentry.getTime().getHour() + ":" + ttentry.getTime().getMinute() + " ; " + 
						 ttentry.getProfessor() + " ; " + ttentry.getRoomNumber());
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
