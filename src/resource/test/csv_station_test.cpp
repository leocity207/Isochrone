#include "csv_station_test.h"

#include "includes/resource/csv/parser/station.h"
#include "includes/resource/csv/engine/string_parser.h"
#include "includes/utils/exception_def.h"



TEST_F(CSV_Station_Test, reading_test_easy)
{
	std::string test = 
"Station1  ;45°31'13\"N; 45°31'13\"E\n\
station2; 45°31'13\"N;45°31'13\"E\n\
station3; 45°31'13\"N;     45°31'13\"E";

	CSV::Engine::String_Parser parser(std::move(test),';');

	std::vector<Station> station_list = CSV::Parser::Station::Parse(parser);

	ASSERT_EQ(station_list.size(), 3);


	ASSERT_EQ(station_list[0].Get_Name(), "Station1");
	ASSERT_EQ(station_list[1].Get_Name(), "station2");
	ASSERT_EQ(station_list[2].Get_Name(), "station3");

	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
	ASSERT_EQ(station_list[0].GetCoordinate(), Sphere_Coordinate("45°31'13\"N", "45°31'13\"E"));
}

TEST_F(CSV_Station_Test, reading_test_hard)
{
	std::string test = 
"Collège Grange              ;45°32'50.9\"N;4°51'48.6\"E\n\
Bon Accueil                  ;45°32'37.4\"N;4°51'58.3\"E\n\
La Réclusière                ;45°32'29.9\"N;4°52'06.3\"E\n\
Les Charavelles              ;45°32'22.5\"N;4°52'14.2\"E\n\
Jean Jaurès                  ;45°32'14.5\"N;4°52'22.7\"E\n\
Place d'Arpot                ;45°32'05.8\"N;4°52'28.5\"E\n\
Diderot                      ;45°31'57.5\"N;4°52'27.4\"E\n\
Les Portes de Lyon           ;45°32'00.7\"N;4°52'24.0\"E\n\
Tuilerie                     ;45°31'50.4\"N;4°52'26.5\"E\n\
Jeu de Paume                 ;45°31'37.6\"N;4°52'23.7\"E\n\
Saint Maurice                ;45°31'27.7\"N;4°52'16.0\"E\n\
Jardin de Ville              ;45°31'19.7\"N;4°52'13.2\"E\n\
Gare de Vienne               ;45°31'16.7\"N;4°52'26.7\"E\n\
Gare de Vienne A             ;45°31'16.7\"N;4°52'26.7\"E\n\
Gare de Vienne D             ;45°31'16.7\"N;4°52'26.7\"E\n\
Lycée E.Fitzgerald           ;45°31'47.1\"N;4°51'55.7\"E\n\
Nicolas Chorier              ;45°31'37.2\"N;4°52'41.7\"E\n\
Temple de Cybèle             ;45°31'28.5\"N;4°52'36.8\"E\n\
Les Célestes                 ;45°31'27.7\"N;4°52'39.6\"E\n\
Les Tupinières               ;45°31'23.1\"N;4°52'51.5\"E\n\
L'Octroi                     ;45°31'13.4\"N;4°53'03.4\"E\n\
La Passardière               ;45°31'02.7\"N;4°53'18.9\"E\n\
La Petite Rente              ;45°30'53.0\"N;4°53'28.4\"E\n\
Saint Benoît                 ;45°30'45.8\"N;4°53'47.7\"E\n\
Roche Claire                 ;45°30'48.1\"N;4°53'56.3\"E\n\
Collonge                     ;45°30'50.2\"N;4°54'12.0\"E\n\
Jean Monnet                  ;45°30'52.8\"N;4°54'25.0\"E\n\
Saint Ignace                 ;45°30'54.7\"N;4°54'30.9\"E\n\
Les Hauts de Malissol        ;45°30'53.9\"N;4°54'39.6\"E\n\
Les Hameaux de Malissol      ;45°30'54.1\"N;4°54'46.5\"E\n\
Malissol La Ferme            ;45°30'53.1\"N;4°54'55.1\"E\n\
L'Horloge                    ;45°30'51.5\"N;4°55'03.2\"E\n\
Les Cèdres                   ;45°31'01.0\"N;4°55'07.8\"E\n\
Rond-Point Malissol          ;45°31'08.3\"N;4°55'06.7\"E\n\
Malissol La Gère             ;45°31'04.2\"N;4°55'19.1\"E\n\
L'Abbaye                     ;45°31'17.5\"N;4°55'15.3\"E\n\
Frèrejean                    ;45°31'26.4\"N;4°55'09.9\"E\n\
Z.A. de Montplaisir Calor    ;45°31'27.1\"N;4°55'13.8\"E\n\
Z.A de Montplaisir           ;45°31'27.1\"N;4°55'13.8\"E\n\
Estrablin Bréguet            ;45°31'13.3\"N;4°55'33.4\"E\n\
Tabourette Routier           ;45°30'57.1\"N;4°56'09.8\"E\n\
Estrablin le Pinay           ;45°30'57.2\"N;4°56'40.6\"E\n\
Perrière                     ;45°30'44.9\"N;4°57'21.2\"E\n\
Le Village                   ;45°31'00.0\"N;4°57'53.2\"E\n\
Le Bois Balay                ;45°31'00.8\"N;4°57'31.3\"E\n\
Stade de Malissol            ;45°31'00.6\"N;4°54'28.6\"E\n\
Malissol Victor Hugo         ;45°30'57.7\"N;4°54'42.5\"E\n\
Champ de Course              ;45°31'32.2\"N;4°55'32.6\"E\n\
La Feyta                     ;45°31'37.6\"N;4°55'37.2\"E\n\
Plan des Aures               ;45°31'40.0\"N;4°55'20.8\"E\n\
Les Gentianes                ;45°31'39.4\"N;4°55'05.1\"E\n\
Les Mésanges                 ;45°31'38.9\"N;4°54'56.8\"E\n\
Centre Pont-Evêque           ;45°31'48.0\"N;4°54'43.9\"E\n\
Les Bleuets                  ;45°31'50.5\"N;4°54'33.7\"E\n\
Les Forges                   ;45°31'50.4\"N;4°54'20.6\"E\n\
La Véga                      ;45°31'47.6\"N;4°54'09.6\"E\n\
Roncevaux                    ;45°31'32.3\"N;4°54'26.2\"E\n\
Charlemangne                 ;45°31'36.2\"N;4°54'13.7\"E\n\
Le Hameaux de Charlemangne   ;45°31'36.2\"N;4°54'13.7\"E\n\
La Ravat                     ;45°31'27.5\"N;4°53'31.4\"E\n\
Champs de Mars               ;45°31'17.0\"N;4°52'16.1\"E\n\
Cours Verdun                 ;45°31'11.8\"N;4°52'14.1\"E\n\
Michel Servet                ;45°31'04.6\"N;4°52'10.9\"E\n\
La Pyramide                  ;45°30'59.1\"N;4°52'07.4\"E\n\
Denfert Rochereau            ;45°30'54.4\"N;4°52'04.4\"E\n\
Le Trente                    ;45°30'46.4\"N;4°51'56.0\"E\n\
Parmentier                   ;45°30'37.1\"N;4°51'45.0\"E\n\
Jean Moulin                  ;45°30'28.7\"N;4°51'34.3\"E\n\
Lycée Galilée                ;45°30'14.7\"N;4°51'16.6\"E\n\
Saint-Avour                  ;45°30'09.1\"N;4°51'09.6\"E\n\
Notre-Dame de l'Isle         ;45°30'13.6\"N;4°51'04.6\"E\n\
Parc Relais Sud de L'Isle    ;45°30'07.8\"N;4°50'55.5\"E\n\
Collège de l'Isle            ;45°30'20.0\"N;4°51'06.9\"E\n\
Estressin Centre Commercial  ;45°32'32.2\"N;4°51'01.3\"E\n\
Estressin Z.I.               ;45°32'31.5\"N;4°51'17.3\"E\n\
Claude Bernard               ;45°32'28.6\"N;4°51'24.6\"E\n\
Savoie                       ;45°32'25.7\"N;4°51'29.7\"E\n\
Centre Social                ;45°32'25.7\"N;4°51'42.4\"E\n\
Pierre et Marie Curie        ;45°32'28.9\"N;4°51'44.0\"E\n\
Cité Jardin                  ;45°32'26.2\"N;4°51'54.6\"E\n\
Gare d'Estressin             ;45°32'24.7\"N;4°52'02.5\"E\n\
Port au Prince               ;45°32'16.6\"N;4°52'04.9\"E\n\
Étienne Rey                  ;45°32'13.2\"N;4°52'09.2\"E\n\
Pasteur                      ;45°32'08.4\"N;4°52'17.3\"E\n\
tullerie                     ;45°31'50.4\"N;4°52'26.4\"E\n\
Les Portes de Lyon           ;45°32'00.7\"N;4°52'23.8\"E\n\
Cuvière                      ;45°31'44.7\"N;4°52'40.8\"E\n\
Place Drapière               ;45°31'40.1\"N;4°52'47.4\"E\n\
École Maupas                 ;45°31'47.4\"N;4°52'55.7\"E\n\
Boulevard Maupas             ;45°31'55.2\"N;4°53'03.3\"E\n\
Maison d'Enfants             ;45°32'05.6\"N;4°53'11.6\"E\n\
Hameau Guillemottes          ;45°32'09.7\"N;4°53'16.2\"E\n\
Guillemottes                 ;45°32'13.2\"N;4°53'10.8\"E\n\
Mont Salomon                 ;45°32'11.8\"N;4°52'59.1\"E\n\
Hôpital L. Hussel            ;45°32'07.4\"N;4°52'51.9\"E\n\
Hôpital-Gérontologie         ;45°31'57.3\"N;4°52'55.4\"E\n\
Rabelais                     ;45°31'37.6\"N;4°52'56.7\"E\n\
Victor Faugier               ;45°31'33.0\"N;4°53'04.4\"E\n\
L. Revol                     ;45°31'29.7\"N;4°53'16.9\"E\n\
Lafayette                    ;45°31'29.2\"N;4°53'23.3\"E\n\
Comte Rolland                ;45°31'38.1\"N;4°53'52.1\"E\n\
Le Pont                      ;45°31'46.1\"N;4°54'06.2\"E\n\
Rés. de Cancanne             ;45°31'52.8\"N;4°54'05.2\"E\n\
Cancanne                     ;45°32'01.3\"N;4°54'13.0\"E\n\
Les Tanneries                ;45°31'59.8\"N;4°54'45.4\"E\n\
Le St-Georges                ;45°31'56.2\"N;4°54'36.5\"E\n\
Les Genêts                   ;45°31'52.9\"N;4°54'26.7\"E\n\
Clair de Lune                ;45°31'49.6\"N;4°55'10.5\"E\n\
La Revolée                   ;45°31'51.7\"N;4°55'24.0\"E\n\
Collège Brassens             ;45°31'42.4\"N;4°55'33.9\"E\n\
Z.I. Seyssuel Tuilerie       ;45°33'12.7\"N;4°49'48.9\"E\n\
Z.I. Seyssuel Les Gardières  ;45°33'19.8\"N;4°49'41.8\"E\n\
Z.I. Seyssuel Restaurant     ;45°33'32.4\"N;4°49'27.1\"E\n\
Centre Commercial Escalières ;45°34'26.5\"N;4°48'41.8\"E\n\
Centre Commercial Devalors   ;45°34'33.0\"N;4°48'38.1\"E\n\
Place Jules Ferry            ;45°34'48.5\"N;4°48'21.1\"E\n\
Cimetière de Chasse          ;45°35'02.3\"N;4°48'10.2\"E\n\
Avenue F. Mitterrand         ;45°34'59.8\"N;4°47'52.8\"E\n\
Barbières Mendès France      ;45°35'04.4\"N;4°47'44.9\"E\n\
Barbières 19 mars 1962       ;45°35'07.7\"N;4°47'53.6\"E\n\
Quartier Gare                ;45°34'52.6\"N;4°47'38.6\"E\n\
Cité Berquet                 ;45°35'00.1\"N;4°47'30.5\"E\n\
Rond-Point Flevieu           ;45°35'12.6\"N;4°47'14.1\"E\n\
Z.I. de l'Islon              ;45°35'01.7\"N;4°47'03.0\"E\n\
Chemin de la Loge            ;45°31'12.0\"N;4°52'27.0\"E\n\
Bel Air                      ;45°31'01.6\"N;4°52'24.4\"E\n\
Hermitage                    ;45°30'50.9\"N;4°52'22.4\"E\n\
Coupe-Jarret                 ;45°30'42.3\"N;4°52'24.3\"E\n\
Les Hauts de Vienne          ;45°30'50.0\"N;4°52'35.8\"E\n\
Les Grands Prés              ;45°30'58.7\"N;4°52'46.4\"E\n\
Beauregard Le Haut           ;45°30'31.4\"N;4°53'03.3\"E\n\
Beauregard Le Grillet        ;45°30'50.3\"N;4°53'03.4\"E\n\
Beauregard                   ;45°31'08.5\"N;4°52'42.8\"E\n\
Burgondes                    ;45°31'11.7\"N;4°52'42.4\"E\n\
Gare de Givors-Ville         ;45°35'04.8\"N;4°45'59.6\"E\n\
Place de la Liberté          ;45°35'06.4\"N;4°46'31.1\"E\n\
Port de Bief                 ;45°34'48.9\"N;4°46'46.2\"E\n\
Tour de Bans                 ;45°34'38.1\"N;4°47'16.6\"E\n\
La Lone                      ;45°34'30.8\"N;4°47'26.6\"E\n\
Freyssinet Rd386             ;45°34'04.5\"N;4°47'58.2\"E\n\
Gare Sncf                    ;45°33'50.1\"N;4°48'15.5\"E\n\
Place Libération             ;45°33'40.4\"N;4°48'27.2\"E\n\
Capas                        ;45°33'32.8\"N;4°48'36.5\"E\n\
La Roche Moussy              ;45°33'23.7\"N;4°48'47.2\"E\n\
Hameau Barlet                ;45°32'26.1\"N;4°50'07.5\"E\n\
Chemin de la Lone            ;45°32'15.2\"N;4°51'19.1\"E\n\
Village                      ;45°32'05.9\"N;4°51'37.3\"E\n\
Lycée Ella Fitzgerald        ;45°31'53.0\"N;4°51'49.1\"E\n\
Mairie                       ;45°31'30.1\"N;4°52'02.9\"E\n\
Trénel                       ;45°31'22.9\"N;4°51'58.5\"E\n\
Centre Nautique              ;45°30'45.5\"N;4°51'09.5\"E\n\
Vérenay                      ;45°30'11.8\"N;4°50'02.8\"E\n\
La Roche                     ;45°29'26.7\"N;4°48'53.8\"E\n\
Place de L’Eglise            ;45°29'19.1\"N;4°48'30.4\"E\n\
Le Goutay                    ;45°29'13.6\"N;4°47'54.0\"E\n\
Tupin                        ;45°29'01.0\"N;4°47'22.6\"E\n\
Collège le Bassenon          ;45°28'15.1\"N;4°46'33.3\"E\n\
Bassenon                     ;45°28'07.1\"N;4°46'26.2\"E\n\
Centre                       ;45°27'44.5\"N;4°46'07.8\"E\n\
Salle de L’Arbuel            ;45°27'38.3\"N;4°45'55.4\"E\n\
Centre Hospitalier           ;45°27'30.3\"N;4°45'35.8\"E\n\
La Maladière                 ;45°27'26.9\"N;4°45'27.1\"E\n\
IME la Bâtie                 ;45°32'07.1\"N;4°52'53.5\"E\n";



CSV::Engine::String_Parser parser(std::move(test), ';');

std::vector<Station> station_list = CSV::Parser::Station::Parse(parser);

ASSERT_EQ(station_list.size(), 163);

}


TEST_F(CSV_Station_Test, baddly_formated)
{
	std::string test =

"Station1  ;45°31'13\"N; 45°31'13\"E\n\
station2; 45°31'13\"N\n\
station3; 45°31'13\"N;     45°31'13\"E";

	CSV::Engine::String_Parser parser(std::move(test), ';');

	EXPECT_THROW(std::vector<Station> station_list = CSV::Parser::Station::Parse(parser), READING_FILE_ERROR);
}


TEST_F(CSV_Station_Test, bad_angle)
{
	std::string test =
		"Station1  ;45°31'13\"N; 45°31'13\"E\n\
station2; 45°31'13\"N;45°3113\"E\n\
station3; 45°31'13\"N;     45°31'13\"E";

	CSV::Engine::String_Parser parser(std::move(test), ';');

	EXPECT_THROW(std::vector<Station> station_list = CSV::Parser::Station::Parse(parser), ANGLE_BADLY_FORMATED);
}


TEST_F(CSV_Station_Test, bad_angle_2)
{
	std::string test =
		"Station1  ;45°31'13\"N; 45°31'13\"E\n\
station2; 45°31'13\"N;36°32''13\"E\n\
station3; 45°31'13\"N;     45°31'13\"E";

	CSV::Engine::String_Parser parser(std::move(test), ';');

	EXPECT_THROW(std::vector<Station> station_list = CSV::Parser::Station::Parse(parser), ANGLE_BADLY_FORMATED);
}

TEST_F(CSV_Station_Test, bad_angle_3)
{
	std::string test =
		"Station1  ;45°31'13\"N; 45°31'13\"E\n\
station2; 45°31'13\"N;367°32'413\"E\n\
station3; 45°31'13\"N;     45°ä31'13\"E";

	CSV::Engine::String_Parser parser(std::move(test), ';');

	EXPECT_THROW(std::vector<Station> station_list = CSV::Parser::Station::Parse(parser), ANGLE_BADLY_FORMATED);
}