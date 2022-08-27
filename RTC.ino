
String RTCdate() {
  DateTime now = rtc.now();
  String  temps = "";
  temps += (daysOfTheWeek[now.dayOfTheWeek()]);
  temps += " ";
  temps += now.day();
  temps += "/";
  temps += now.month();
  temps += "/";
  temps += now.year();
  return temps;
}

String RTCdateenvoie() {
  DateTime now = rtc.now();
  String  temps = "";
  temps += now.year();
  temps += "/";
  temps += now.month();
  temps += "/";
  temps += now.day();
  return temps;
}

String RTCheure() {
  DateTime now = rtc.now();
  String temps = "";
  temps += now.hour();
  temps += ":";
  temps += now.minute();
  temps += ":";
  temps += now.second();
  return temps;
}
