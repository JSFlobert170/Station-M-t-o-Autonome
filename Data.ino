String donnee() {
  String meteo = "";
  meteo += RTCdateenvoie();
  meteo += ";";
  meteo += RTCheure();
  meteo += ";";
  meteo += temp();
  meteo += ";";
  meteo += lum();
  meteo += ";";
  meteo += pressure();
  meteo += ";";
  meteo += humidity();
  meteo += ";";
  meteo += get_wind_speed();
  meteo += ";";  
  meteo += GPS();
  meteo += ";";
  meteo += printWeather();
  meteo += ";";
  meteo += calcWeather();
  meteo += ";";
  meteo += tension();
  return meteo;
}
