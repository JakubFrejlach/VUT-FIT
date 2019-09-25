# IPK - projekt 1 - varianta 2 - Open Weather Map API
  - Autor - Jakub Frejlach (xfrejl00)
  - Psáno v jazyce Python3.6
### Úkol
Úkolem je vytvořit program, který pomocí HTTP dotazů zprostředkuje data o počasí z OpenWeatherMap API. Pro zaslaní platného dotazu je nutný validní API klíč, který lze bezplatně získat při registraci na OpenWeatherMap.

### Řešení
Pro řešení problému budeme potřebovat importovat několik knihoven a to socket, json a sys. Sys z důvodu získání potřebných argumentů spouštěného programu, v našem případě API klíč pro autorizaci a název požadovaného města. Pomocí sys lze též zajistit, aby měl spouštěný program správný počet argumentů. Adresu serveru lze zjistit z dokumentace API (api.openweathermap.org), port pomocí vývojářského nástroje pro prohlížeč (80). Dále vytvoříme socket a pomocí něho pošleme HTTP dotaz na server. U socketu je nutno zkontrolovat jeho file descriptor, který je v případě chyby "-1", a poté zkusit připojení na server a v případě neúspěchu zachytit vyjímku a ukončit program. Server poskytuje data v různých formátech (HTML, XML, JSON). Já jsem zvolil JSON formát. Z přijatých dat vyextrahujeme pomocí split či regexu návratový kód a zbavíme se HTTP hlavičky, abychom získali korektní JSON formát. Z návratového kódu ověříme, zda-li se dotaz povedl (kód "200 OK"). Při úspěchu dotazu načteme získaná do JSONu a z tohoto formátu už posléze pouze vypisujeme data o počasí. Je nutno ošetřit směr větru (wind-deg), který v získaných datech občas chybí.

### Instalace a překlad aplikace
Aplikaci je nutno stáhnout do svého počítače a pro spuštění je nutno mít nainstalovaný **python3.6** a balíček **make**.

### Spuštění aplikace
Aplikace se spouští přes následující příkaz
```sh
$ make run api_key=<API klíč> city=<město>
```
Pro správný běh aplikace se přepokládá funkční API klíč a existující město. API klíč lze získat zaregistrováním se na této stránce https://openweathermap.org/. Po registraci vám přijde na vámi zadaný email klíč, který by měl být nejdéle do dvou hodin aktivován.

Při korektním klíči a názvu města se očekává výstup ve formátu:
```sh
Prague
clear sky
Temperature: 0.43°C
Humidity: 50%
Pressure: 1038hPa
Wind speed: 11.16km/h
Wind deg: 230
```

**Známé návratové kódy dotazu:**
  - 200 - OK
  - 400 - Bad request
  - 401 - Unauthorized
  - 404 - Not found
### Omezení
  - Aplikace spoléhá na aktuální formát přijímaných dat, v případě změny tohoto formátu je nutno upravit způsob ořezávání HTTP hlavičky a extrakce návratového kódu.
