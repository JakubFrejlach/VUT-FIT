----------------------------------------------------------
----------------------- Cast 2/5 -------------------------
----------------------------------------------------------

DROP TABLE zamestnanec CASCADE CONSTRAINT;
DROP TABLE vedouci CASCADE CONSTRAINT;
DROP TABLE bezny_zamestnanec CASCADE CONSTRAINT;
DROP TABLE dozorce CASCADE CONSTRAINT;
DROP TABLE paserak CASCADE CONSTRAINT;

DROP TABLE pecivo CASCADE CONSTRAINT;
DROP TABLE surovina CASCADE CONSTRAINT;

DROP TABLE smena CASCADE CONSTRAINT;
DROP TABLE objednavka CASCADE CONSTRAINT;
DROP TABLE veznice CASCADE CONSTRAINT;
DROP TABLE vezen CASCADE CONSTRAINT;

DROP TABLE objednavka_obsahuje_pecivo CASCADE CONSTRAINT;
DROP TABLE vedoci_planuje_vyrobu CASCADE CONSTRAINT;
DROP TABLE pecivo_obsahuje_surovinu CASCADE CONSTRAINT;
DROP TABLE dozorce_vykonava_smenu CASCADE CONSTRAINT;
DROP TABLE paserak_domlouva_dozorce CASCADE CONSTRAINT;
DROP SEQUENCE seq_id_zamestnace;

CREATE TABLE zamestnanec (
    id_zamestnance NUMBER NOT NULL,
    jmeno VARCHAR(32),
    rodne_cislo VARCHAR(11),
    nastup_do_funkce DATE,
    typ_uvazku VARCHAR(16),
    datum_narozeni DATE,
    CONSTRAINT pk_zamestnanec PRIMARY KEY (id_zamestnance)
);
CREATE TABLE vedouci (
    id_zamestnance NUMBER NOT NULL,
    titul VARCHAR(16),
    doba_praxe NUMBER,
    CONSTRAINT pk_vedouci PRIMARY KEY (id_zamestnance) 
);
CREATE TABLE bezny_zamestnanec (
    id_zamestnance NUMBER NOT NULL,
    pozice VARCHAR(32),
    CONSTRAINT pk_bezny_zamestnanec PRIMARY KEY (id_zamestnance)
);
CREATE TABLE dozorce (
    id_zamestnance NUMBER NOT NULL,
    proverka NUMBER,
    id_veznice NUMBER,
    CONSTRAINT pk_dozorce PRIMARY KEY (id_zamestnance)
);
CREATE TABLE paserak (
    id_zamestnance NUMBER NOT NULL,
    spolehlivost VARCHAR(4),
    CONSTRAINT pk_paserak PRIMARY KEY (id_zamestnance)
);

CREATE TABLE pecivo (
    id_peciva NUMBER GENERATED ALWAYS AS IDENTITY,
    jmeno VARCHAR(32),
    druh_peciva VARCHAR(32),
    hmotnost NUMBER,
    bezlepkovost VARCHAR(3),
    alergeny VARCHAR(32),
    CONSTRAINT pk_pecivo PRIMARY KEY (id_peciva)
);

CREATE TABLE surovina (
    id_suroviny NUMBER GENERATED ALWAYS AS IDENTITY,
    jmeno VARCHAR(32),
    mnozstvi NUMBER,
    nakupni_cena NUMBER,
    CONSTRAINT pk_surovina PRIMARY KEY (id_suroviny)
);

CREATE TABLE smena (
    id_smeny NUMBER GENERATED ALWAYS AS IDENTITY,
    zacatek TIMESTAMP,
    konec TIMESTAMP,
    blok VARCHAR(1),
    CONSTRAINT pk_smena PRIMARY KEY (id_smeny)
);

CREATE TABLE objednavka (
    id_objednavky NUMBER GENERATED ALWAYS AS IDENTITY,
    cena NUMBER,
    termin_dodani DATE,
    zapecene_predmety Varchar(100),
    id_zamestnance NUMBER NOT NULL,
    id_paseraka NUMBER NOT NULL,
    id_vezne NUMBER NOT NULL,
    CONSTRAINT pk_objednavka PRIMARY KEY (id_objednavky)
);

CREATE TABLE veznice (
    id_veznice NUMBER GENERATED ALWAYS AS IDENTITY,
    jmeno VARCHAR(32),
    adresa VARCHAR(64),
    uroven_ostrahy VARCHAR(16), -- ? slovne nebo ciselne
    kapacita NUMBER,
    CONSTRAINT pk_veznice PRIMARY KEY (id_veznice)
);

CREATE TABLE vezen (
    id_vezne NUMBER GENERATED ALWAYS AS IDENTITY,
    jmeno VARCHAR(32),
    datum_narozeni DATE,
    delka_trestu NUMBER,
    typ_cely VARCHAR(16),
    id_veznice NUMBER NOT NULL,
    CONSTRAINT pk_vezen PRIMARY KEY (id_vezne)
);

-- Rozlozeni N:M vazeb
CREATE TABLE objednavka_obsahuje_pecivo (
    pocet NUMBER NOT NULL,
    id_peciva NUMBER NOT NULL,
    id_objednavky NUMBER NOT NULL,
    CONSTRAINT pk_objednavka_obsahuje_pecivo PRIMARY KEY (id_peciva,id_objednavky)
);
CREATE TABLE vedoci_planuje_vyrobu (
    pocet NUMBER NOT NULL,
    id_peciva NUMBER NOT NULL,
    id_zamestnance NUMBER NOT NULL,
    CONSTRAINT pk_vedoci_planuje_vyrobu PRIMARY KEY (id_peciva,id_zamestnance)
);
CREATE TABLE pecivo_obsahuje_surovinu (
    id_suroviny NUMBER NOT NULL,
    id_peciva NUMBER NOT NULL,
    CONSTRAINT pk_pecivo_obsahuje_surovinu PRIMARY KEY (id_peciva,id_suroviny)
);
CREATE TABLE dozorce_vykonava_smenu (
    id_smeny NUMBER NOT NULL,
    id_zamestnance NUMBER NOT NULL,
    CONSTRAINT pk_dozorce_vykonava_smenu PRIMARY KEY (id_smeny,id_zamestnance)
);
CREATE TABLE paserak_domlouva_dozorce (
    id_dozorce NUMBER NOT NULL,
    id_paseraka NUMBER NOT NULL,
    CONSTRAINT pk_paserak_domlouva_dozorce PRIMARY KEY (id_paseraka, id_dozorce)
);

----------------------------------------------------------
-------------------Cizi klice (vazby)---------------------
----------------------------------------------------------

--specializace
ALTER TABLE vedouci ADD CONSTRAINT fk_vedouci FOREIGN KEY (id_zamestnance) REFERENCES zamestnanec (id_zamestnance);
ALTER TABLE bezny_zamestnanec ADD CONSTRAINT fk_bezny_zamestnanec FOREIGN KEY (id_zamestnance) REFERENCES zamestnanec (id_zamestnance);
ALTER TABLE dozorce ADD CONSTRAINT fk_dozorce FOREIGN KEY (id_zamestnance) REFERENCES zamestnanec (id_zamestnance);
ALTER TABLE paserak ADD CONSTRAINT fk_paserak FOREIGN KEY (id_zamestnance) REFERENCES zamestnanec (id_zamestnance);


-- vezen
ALTER TABLE vezen ADD CONSTRAINT fk_je_veznen_v FOREIGN KEY (id_veznice) REFERENCES veznice (id_veznice) ON DELETE CASCADE;

-- objednavka
ALTER TABLE objednavka ADD CONSTRAINT fk_vytvari FOREIGN KEY (id_vezne) REFERENCES vezen (id_vezne) ON DELETE CASCADE;
ALTER TABLE objednavka ADD CONSTRAINT fk_pasuje FOREIGN KEY (id_paseraka) REFERENCES paserak (id_zamestnance) ON DELETE CASCADE;
ALTER TABLE objednavka ADD CONSTRAINT fk_vyrizuje FOREIGN KEY (id_zamestnance) REFERENCES bezny_zamestnanec (id_zamestnance) ON DELETE CASCADE;

--dozorce
ALTER TABLE dozorce ADD CONSTRAINT fk_pracuje_v FOREIGN KEY (id_veznice) REFERENCES veznice (id_veznice) ON DELETE CASCADE;

--objednavka_obsahuje_pecivo
ALTER TABLE objednavka_obsahuje_pecivo ADD CONSTRAINT fk_obsahuje_pecivo FOREIGN KEY (id_peciva) REFERENCES pecivo (id_peciva) ON DELETE CASCADE;
ALTER TABLE objednavka_obsahuje_pecivo ADD CONSTRAINT fk_objednavka_obsahuje FOREIGN KEY (id_objednavky) REFERENCES objednavka (id_objednavky) ON DELETE CASCADE;

--vedoci_planuje_vyrobu
ALTER TABLE vedoci_planuje_vyrobu ADD CONSTRAINT fk_vedouci_planuje FOREIGN KEY (id_zamestnance) REFERENCES vedouci (id_zamestnance) ON DELETE CASCADE;
ALTER TABLE vedoci_planuje_vyrobu ADD CONSTRAINT fk_planuje_pecivo FOREIGN KEY (id_peciva) REFERENCES pecivo (id_peciva) ON DELETE CASCADE;

--pecivo_obsahuje_surovinu
ALTER TABLE pecivo_obsahuje_surovinu ADD CONSTRAINT fk_obsahuje_surovinu FOREIGN KEY (id_suroviny) REFERENCES surovina (id_suroviny) ON DELETE CASCADE;
ALTER TABLE pecivo_obsahuje_surovinu ADD CONSTRAINT fk_pecivo_obsahuje FOREIGN KEY (id_peciva) REFERENCES pecivo (id_peciva) ON DELETE CASCADE;

--dozorce_vykonava_smenu
ALTER TABLE dozorce_vykonava_smenu ADD CONSTRAINT fk_dozorce_vykonava FOREIGN KEY (id_zamestnance) REFERENCES dozorce (id_zamestnance) ON DELETE CASCADE;
ALTER TABLE dozorce_vykonava_smenu ADD CONSTRAINT fk_vykonava_smenu FOREIGN KEY (id_smeny) REFERENCES smena (id_smeny) ON DELETE CASCADE;

--paserak_domlouva_dozorce
ALTER TABLE paserak_domlouva_dozorce ADD CONSTRAINT fk_dozorce_domlouva FOREIGN KEY (id_dozorce) REFERENCES dozorce (id_zamestnance) ON DELETE CASCADE;
ALTER TABLE paserak_domlouva_dozorce ADD CONSTRAINT fk_paserak_domlouva FOREIGN KEY (id_paseraka) REFERENCES paserak (id_zamestnance) ON DELETE CASCADE;

----------------------------------------------------------
-------------------------Triggery-------------------------
----------------------------------------------------------


--Trigger pro kontrolu rodneho cisla

CREATE OR REPLACE TRIGGER check_rodne_cislo
BEFORE INSERT OR UPDATE OF rodne_cislo ON zamestnanec
FOR EACH ROW 
DECLARE
    mesic NUMBER(2);
    den NUMBER(2);
    rok NUMBER(2);
    cislo NUMBER(10);
BEGIN 

    IF NOT REGEXP_LIKE (:NEW.rodne_cislo, '^\d\d\d\d\d\d/\d\d\d\d$') THEN
        RAISE_APPLICATION_ERROR(-20000,'Nespravny format rodneho cisla');
    END IF;


    rok := CAST(SUBSTR(:NEW.rodne_cislo,1,2) AS NUMBER);
    mesic :=  CAST(SUBSTR(:NEW.rodne_cislo,3,2) AS NUMBER);
    den :=  CAST(SUBSTR(:NEW.rodne_cislo,5,2) AS NUMBER);
    cislo := CAST(CONCAT(SUBSTR(:NEW.rodne_cislo,1,6),SUBSTR(:NEW.rodne_cislo,8,4)) AS NUMBER);

    IF NOT (MOD(cislo,11) = 0) THEN
        RAISE_APPLICATION_ERROR(-20004,'Rodne cislo neni delitelne 11');
    END IF;

    IF NOT (((mesic = 1 OR mesic = 3 OR mesic = 5 OR mesic = 7 OR mesic = 8 OR mesic = 10 OR mesic = 12 OR mesic = 51 OR mesic = 53 OR mesic = 55 OR mesic = 57 OR mesic = 60 OR mesic = 62) AND den BETWEEN 1 AND 31) OR
        ((mesic = 4 OR mesic = 6 OR mesic = 9 OR mesic = 11 OR mesic = 54 OR mesic = 56 OR mesic = 59 OR mesic = 61) AND den BETWEEN 1 AND 30) OR ((mesic = 2 OR mesic = 52) AND den BETWEEN 1 AND 28))THEN
        RAISE_APPLICATION_ERROR(-20002,'Nespravne datum v rodnem cisle');
    END IF;

END;
/

--Inkrementace ID zamestnance
CREATE SEQUENCE seq_id_zamestnace;

CREATE OR REPLACE TRIGGER inc_zamestnanec_id 
BEFORE INSERT ON zamestnanec
   FOR EACH ROW
BEGIN
    :NEW.id_zamestnance := seq_id_zamestnace.nextval;
END;
/
----------------------------------------------------------
------------------------Procedury-------------------------
----------------------------------------------------------

-- Procedura vypise procento uveznenych veznu ze vsech veznu v databazi, kteri jsou drzeni ve veznici se zadanym id
CREATE OR REPLACE PROCEDURE procenta_veznu_ve_veznici(id_v NUMBER) IS
    CURSOR c_veznice IS SELECT * FROM vezen;
    i_veznice c_veznice%ROWTYPE;
    veznu_celkem NUMBER;
    veznu_ve_veznici NUMBER;
    procento NUMBER;
    jmeno_veznice veznice.jmeno%TYPE;
BEGIN
    veznu_celkem := 0;
    veznu_ve_veznici := 0;
    procento := 0;
    SELECT jmeno INTO jmeno_veznice FROM veznice WHERE id_v = id_veznice;
    open c_veznice;
    loop
        fetch c_veznice into i_veznice;
        exit when c_veznice%NOTFOUND;
        IF (i_veznice.id_veznice = id_v) THEN
            veznu_ve_veznici := veznu_ve_veznici + 1;
        END IF;
        veznu_celkem := veznu_celkem + 1;
    end loop;
    procento := ROUND((veznu_ve_veznici / veznu_celkem)*100,2);
    dbms_output.put_line('Ve veznici ' || jmeno_veznice || ' je umisteno ' || procento || '% veznu z databaze.');
EXCEPTION
    WHEN zero_divide THEN
        dbms_output.put_line('Ve veznici ' || jmeno_veznice || ' neni uveznen zadny vezen.');
    WHEN others THEN
        RAISE_APPLICATION_ERROR(-20003,'Procedura selhala.');
END;
/

-- Procedura zkontroluje vsechny vezne, zda-li neprekrocili zadany limit objednavek za urcity interval.
-- Interval je voliteny pomoci parametru datum_od a datum_do. Pokud se najde vezen, ktery tento limit prekrocil,
-- je povazovan za nebezpecneho (vlastnictvi vetsiho mnostvi kontrabandu) a je presunut na samotku.
CREATE OR REPLACE PROCEDURE zkontroluj_vezne(limit_objednavek NUMBER, datum_od DATE, datum_do DATE) IS
   CURSOR c_vezni IS SELECT * FROM vezen;
   CURSOR c_objednavky is SELECT * FROM objednavka;
   i_vezen c_vezni%ROWTYPE;
   i_objednavka c_objednavky%ROWTYPE;
   objednavek_za_interval NUMBER;
BEGIN
    objednavek_za_interval := 0;
    OPEN c_vezni;
    LOOP
        FETCH c_vezni INTO i_vezen;
        EXIT WHEN c_vezni%NOTFOUND;
        OPEN c_objednavky;
        LOOP
            FETCH c_objednavky into i_objednavka;
            IF c_objednavky%NOTFOUND THEN
                CLOSE c_objednavky;
                IF objednavek_za_interval > limit_objednavek THEN
                    IF i_vezen.typ_cely = 'samotka' THEN
                        dbms_output.put_line('Vezen ' || i_vezen.jmeno || ' prekrocil limit objednavek, ale jiz se nachazi na samotce!');
                    ELSE
                        UPDATE vezen
                        SET typ_cely='samotka'
                        WHERE i_vezen.id_vezne = vezen.id_vezne;
                        dbms_output.put_line('Vezen ' || i_vezen.jmeno || ' prekrocil limit objednavek! Presouva se na samotku!');
                    END IF;
                END IF;
                objednavek_za_interval := 0;
                EXIT;
            END IF;
            IF (i_objednavka.id_vezne = i_vezen.id_vezne and (i_objednavka.termin_dodani BETWEEN datum_od AND datum_do)) THEN
                objednavek_za_interval := objednavek_za_interval + 1;
            END IF;
        END LOOP;
    END LOOP;
END;
/

SET serveroutput ON;


----------------------------------------------------------
-------------------Naplneni (insert)----------------------
----------------------------------------------------------


--zamestnanec
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Lukas Hrib','940830/4719','01.04.2016','Full-time','30.08.1994');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Petr Novak','920201/7913','01.09.2018','Full-time','01.02.1992');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Daniel Rozinka','860718/8810','01.09.2018','Full-time','18.07.1986');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Jiri Kachna','820228/6719','01.04.2012','Full-time','28.02.1982');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Lenka Mala','906212/0012','01.01.2019','Part-time','12.12.1990');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Pavel Dvorak','911112/7212','05.05.2018','Full-time','12.11.1991');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Jan Honza','890130/8119','01.02.2019','Full-time','30.01.1989');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Patrik Hofmann','840130/1117','09.02.2010','Full-time','30.01.1984');
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Zbynek Spatny','999999/1148','19.02.2010','Full-time','31.01.1964'); -- spatne rodne cislo, ukazka triggeru

--vedouci
INSERT INTO vedouci (id_zamestnance,titul,doba_praxe) values ('004','Ing','7');

--bezny_zamestnanec
INSERT INTO bezny_zamestnanec (id_zamestnance,pozice) values ('005','Pekar');
INSERT INTO bezny_zamestnanec (id_zamestnance,pozice) values ('001','Skladnik');

--paserak
INSERT INTO paserak (id_zamestnance,spolehlivost) values ('003','100%');
INSERT INTO paserak (id_zamestnance,spolehlivost) values ('002','98%');

--pecivo
INSERT INTO pecivo (jmeno,druh_peciva,hmotnost,bezlepkovost,alergeny) VALUES ('rohlik','bile','50','ne','1');
INSERT INTO pecivo (jmeno,druh_peciva,hmotnost,bezlepkovost,alergeny) VALUES ('chleb','bile','1200','ne','1,6');
INSERT INTO pecivo (jmeno,druh_peciva,hmotnost,bezlepkovost,alergeny) VALUES ('chleb zitny','bile','450','ne','1,7');
INSERT INTO pecivo (jmeno,druh_peciva,hmotnost,bezlepkovost,alergeny) VALUES ('chleb vicezrnny','celozrnne','350','ano','6');

--surovina
INSERT INTO surovina (jmeno,mnozstvi,nakupni_cena) VALUES ('psenicna mouka','150','15');
INSERT INTO surovina (jmeno,mnozstvi,nakupni_cena) VALUES ('drozdi','15','6');
INSERT INTO surovina (jmeno,mnozstvi,nakupni_cena) VALUES ('zitna mouka','22','22');
INSERT INTO surovina (jmeno,mnozstvi,nakupni_cena) VALUES ('kukuricna mouka','48','31');
INSERT INTO surovina (jmeno,mnozstvi,nakupni_cena) VALUES ('kmin','20','40');
--smena
INSERT INTO smena(zacatek, konec, blok) VALUES ('28.03.2019 07:00:00','28.03.2019 19:00:00','A');
INSERT INTO smena(zacatek, konec, blok) VALUES ('29.03.2019 07:00:00','29.03.2019 19:00:00','A');
INSERT INTO smena(zacatek, konec, blok) VALUES ('30.03.2019 07:00:00','30.03.2019 19:00:00','A');
INSERT INTO smena(zacatek, konec, blok) VALUES ('28.03.2019 19:00:00','29.03.2019 7:00:00','B');
INSERT INTO smena(zacatek, konec, blok) VALUES ('29.03.2019 19:00:00','30.03.2019 7:00:00','B');


--veznice
INSERT INTO veznice (jmeno, adresa, uroven_ostrahy, kapacita) VALUES ('Mirov', 'Mirov 27, 789 53 Mirov', 'Zvysena','369');
INSERT INTO veznice (jmeno, adresa, uroven_ostrahy, kapacita) VALUES ('Kurim', 'Blanenska 1191, 664 34 Kurim', 'Nizka','464');
INSERT INTO veznice (jmeno, adresa, uroven_ostrahy, kapacita) VALUES ('Alcatraz', 'Prison Island 6666, 663 85 San Francisco', 'Vysoka','700');

--vezen
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Jan Odcizil','02.11.1992','24','samotka','2');
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Jiri Zlamal','13.07.1982','42','dvouluzko','2');
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Premysl Novacek','4.4.1974','97','dvouluzko','1');
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Ladislav Kopecek','11.11.1966','6','dvouluzko','2');
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Ondrej Mazanec','27.03.1984','52','ctyrluzko','1');
INSERT INTO vezen (jmeno, datum_narozeni, delka_trestu, typ_cely, id_veznice) VALUES ('Al Capone','03.05.1972','700','samotka','3');


--objednavka
INSERT INTO objednavka (cena, termin_dodani, zapecene_predmety, id_zamestnance, id_paseraka, id_vezne) VALUES ('99','28.03.2019', 'ziletka', '005','3', '2');
INSERT INTO objednavka (cena, termin_dodani, zapecene_predmety, id_zamestnance, id_paseraka, id_vezne) VALUES ('99','29.03.2019', 'sperhak', '005', '3', '3');
INSERT INTO objednavka (cena, termin_dodani, zapecene_predmety, id_zamestnance, id_paseraka, id_vezne) VALUES ('99','15.04.2019', 'cigarety', '005', '2', '4');
INSERT INTO objednavka (cena, termin_dodani, zapecene_predmety, id_zamestnance, id_paseraka, id_vezne) VALUES ('99','30.05.2019', 'sroubovak', '001', '2', '2');
INSERT INTO objednavka (cena, termin_dodani, zapecene_predmety, id_zamestnance, id_paseraka, id_vezne) VALUES ('150','22.05.2019', 'paklic', '001', '3', '2');

--dozorce
INSERT INTO dozorce (id_zamestnance,proverka,id_veznice) VALUES ('006','1','2');
INSERT INTO dozorce (id_zamestnance,proverka,id_veznice) VALUES ('007','4','1');
INSERT INTO dozorce (id_zamestnance,proverka,id_veznice) VALUES ('008','3','1');

--objednavka_obsahuje_pecivo
INSERT INTO objednavka_obsahuje_pecivo (pocet, id_peciva, id_objednavky) VALUES ('10','1','1');
INSERT INTO objednavka_obsahuje_pecivo (pocet, id_peciva, id_objednavky) VALUES ('1','4','2');
INSERT INTO objednavka_obsahuje_pecivo (pocet, id_peciva, id_objednavky) VALUES ('2','4','3');
INSERT INTO objednavka_obsahuje_pecivo (pocet, id_peciva, id_objednavky) VALUES ('10','1','4');
INSERT INTO objednavka_obsahuje_pecivo (pocet, id_peciva, id_objednavky) VALUES ('2','2','4');

--vedoci_planuje_vyrobu
INSERT INTO vedoci_planuje_vyrobu (pocet,id_peciva,id_zamestnance) VALUES ('10','1','004');
INSERT INTO vedoci_planuje_vyrobu (pocet,id_peciva,id_zamestnance) VALUES ('2','4','004');

--pecivo_obsahuje_surovinu
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('1','1');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('2','1');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('1','2');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('2','2');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('5','2');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('2','3');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('3','3');
INSERT INTO pecivo_obsahuje_surovinu (id_suroviny,id_peciva) VALUES ('4','4');

--dozorce_vykonava_smenu
INSERT INTO dozorce_vykonava_smenu (id_smeny, id_zamestnance) VALUES ('1','006');
INSERT INTO dozorce_vykonava_smenu (id_smeny, id_zamestnance) VALUES ('2','006');
INSERT INTO dozorce_vykonava_smenu (id_smeny, id_zamestnance) VALUES ('3','006');
INSERT INTO dozorce_vykonava_smenu (id_smeny, id_zamestnance) VALUES ('4','007');
INSERT INTO dozorce_vykonava_smenu (id_smeny, id_zamestnance) VALUES ('5','007');

--paserak_domlouva_dozorce
INSERT INTO paserak_domlouva_dozorce (id_dozorce, id_paseraka) VALUES ('6','3');

----------------------------------------------------------
----------------------- Cast 3/5 -------------------------
----------------------------------------------------------

--spojeni 2 tabulek

--vsechny objednavky objednane veznem Jirim Zlamalem (upravenim jmena lze zjistit objednavky ostatnich veznu)
SELECT id_objednavky, cena, termin_dodani, zapecene_predmety, jmeno AS vezen
FROM objednavka NATURAL JOIN vezen
WHERE jmeno = 'Jiri Zlamal';

--vybere vsechny veznice, kde se nachazeji vezni na samotkach
SELECT DISTINCT v.id_veznice, v.jmeno
FROM veznice v JOIN vezen k ON k.id_veznice = v.id_veznice
WHERE k.typ_cely = 'samotka';

--spojeni 3 tabulek

--zjisti, kteri zamestnanci s plnym uvazkem meli na starost objednavky pro vezne Jiriho Zlamala a ktere predmety do nich zapekli
SELECT b.id_zamestnance, z.jmeno, o.zapecene_predmety, o.id_objednavky
FROM (bezny_zamestnanec b JOIN zamestnanec z ON z.id_zamestnance = b.id_zamestnance)  
                 JOIN objednavka o ON z.id_zamestnance = o.id_zamestnance
                 JOIN vezen v ON v.id_vezne = o.id_vezne
WHERE v.jmeno = 'Jiri Zlamal' and z.typ_uvazku = 'Full-time';

--klauzule GROUP BY

--zjisti, v kolika typech peciva se vyskytuji jednotlive suroviny
SELECT COUNT(surovina.jmeno) as pocet_vyskytu, surovina.jmeno
FROM pecivo, pecivo_obsahuje_surovinu, surovina
WHERE pecivo.id_peciva = pecivo_obsahuje_surovinu.id_peciva and surovina.id_suroviny = pecivo_obsahuje_surovinu.id_suroviny
GROUP BY surovina.jmeno
ORDER BY pocet_vyskytu;

--zjisti, kolik objednavek maji jednotlivi vezni objednano
SELECT COUNT(o.id_vezne) as pocet_objednavek, k.jmeno, v.jmeno AS nazev_veznice
FROM veznice v JOIN vezen k ON v.id_veznice = k.id_veznice LEFT OUTER JOIN objednavka o ON o.id_vezne = k.id_vezne
GROUP BY k.jmeno, v.jmeno
ORDER BY pocet_objednavek DESC;

--zjisti, kolik objednavek je objednano do jednotlivych veznic
SELECT COUNT(o.id_vezne) as pocet_objednavek, v.jmeno
FROM veznice v JOIN vezen k ON v.id_veznice = k.id_veznice LEFT OUTER JOIN objednavka o ON o.id_vezne = k.id_vezne
GROUP BY v.jmeno
ORDER BY pocet_objednavek DESC;

--predikat EXISTS

--vybere vsechny veznice, kde vezni nejsou ubytovani na ctyrluzkovych celach
SELECT veznice.jmeno
FROM veznice
WHERE NOT EXISTS(
SELECT vezen.jmeno
FROM vezen
WHERE veznice.id_veznice = vezen.id_veznice AND vezen.typ_cely = 'ctyrluzko');

--predikat IN

--vybere vsechny vezne, jejichz objednavka ma byt dorucena v breznu 2019
SELECT vezen.jmeno
FROM vezen
WHERE vezen.id_vezne IN(
SELECT id_vezne
FROM vezen NATURAL JOIN objednavka
WHERE termin_dodani BETWEEN TO_DATE('1.3.2019', 'dd.mm.yyyy') AND TO_DATE('31.3.2019', 'dd.mm.yyyy'));



--volani procedur
SET serveroutput ON;
EXEC procenta_veznu_ve_veznici(1);
EXEC procenta_veznu_ve_veznici(2);
EXEC procenta_veznu_ve_veznici(3);

EXEC zkontroluj_vezne(1, '1.1.2019', '31.12.2019');
EXEC zkontroluj_vezne(2, '1.1.2019', '31.12.2019');
EXEC zkontroluj_vezne(0, '1.1.2019', '31.12.2019');



---------------------------------------------------
-------------Udeleni prav xfrejl00----------------
---------------------------------------------------
GRANT ALL ON zamestnanec TO xfrejl00;
GRANT ALL ON vedouci TO xfrejl00;
GRANT ALL ON bezny_zamestnanec TO xfrejl00;
GRANT ALL ON dozorce TO xfrejl00;
GRANT ALL ON paserak TO xfrejl00;
GRANT ALL ON pecivo TO xfrejl00;
GRANT ALL ON surovina TO xfrejl00;
GRANT ALL ON smena TO xfrejl00;
GRANT ALL ON objednavka TO xfrejl00;
GRANT ALL ON veznice TO xfrejl00;
GRANT ALL ON vezen TO xfrejl00;

GRANT ALL ON objednavka_obsahuje_pecivo TO xfrejl00;
GRANT ALL ON vedoci_planuje_vyrobu TO xfrejl00;
GRANT ALL ON dozorce_vykonava_smenu TO xfrejl00;
GRANT ALL ON paserak_domlouva_dozorce TO xfrejl00;

GRANT EXECUTE ON procenta_veznu_ve_veznici TO xfrejl00;
GRANT EXECUTE ON zkontroluj_vezne TO xfrejl00;

----------------------------------------------------------
----------------------- EXPLAIN PLAN----------------------
----------------------------------------------------------

DROP INDEX index_objednavka_vezen;

EXPLAIN PLAN FOR
SELECT jmeno, SUM(cena) AS cena_celkem FROM vezen JOIN objednavka ON vezen.id_vezne = objednavka.id_vezne GROUP BY jmeno;
SELECT plan_table_output FROM TABLE (dbms_xplan.display());

CREATE INDEX index_objednavka_vezen ON objednavka(cena, id_vezne);

EXPLAIN PLAN FOR
SELECT jmeno, SUM(cena) AS cena_celkem FROM vezen JOIN objednavka ON vezen.id_vezne = objednavka.id_vezne GROUP BY jmeno;
SELECT plan_table_output FROM TABLE (dbms_xplan.display());


----------------------------------------------------------
------------------- Materialized view --------------------
----------------------------------------------------------


DROP MATERIALIZED VIEW zamestnanecView;
CREATE MATERIALIZED VIEW LOG ON zamestnanec WITH PRIMARY KEY, ROWID(typ_uvazku) INCLUDING NEW VALUES;

CREATE MATERIALIZED VIEW zamestnanecView
CACHE   -- optimalizace cteni pohledu
BUILD IMMEDIATE -- pohled se naplni hned po vytvoreni
REFRESH FAST ON COMMIT -- akutalizuje pohled dle logu master tabulek
ENABLE QUERY REWRITE -- bude pouzivan optimalizator
AS SELECT typ_uvazku, count(typ_uvazku) AS pocet_zamestnanych
FROM zamestnanec
GROUP BY typ_uvazku;

GRANT ALL ON zamestnanecView TO xfrejl00;

SELECT * from zamestnanecView;
INSERT INTO zamestnanec (jmeno,rodne_cislo,nastup_do_funkce,typ_uvazku, datum_narozeni) values ('Jiri Novy','000915/7808','1.5.2018','Part-time','15.09.2000');
COMMIT;
SELECT * from zamestnanecView;
