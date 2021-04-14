##----- Kompileringsinstruktioner -----##
Spelet kompileras genom att först skriva 'cmake .' följt av 'make'.
Spelet kan sedan köras med './sfml'.

##----- Användarinstruktioner -----##
Startmenyn kan navigeras med 'W' och 'S' eller 'Up' och 'Ner' piltangent.
Du väljer nuvarande meny med 'Enter'.

Vid val av 'Play' startar spelet.
Där kontrolleras den första spelarens mask med 'A' och 'D' och den andra 
spelarens mask kontrolleras med 'Vänster' och 'Höger' piltangent.
Vid klick av 'Esc' återvänder spelet till startmenyn utan vinnare.
Under spelets gång placeras det slumpmässigt ut mat på spelplanen i olika färger.
- Magenta färgad mat gör masken som kolliderar i den längre.
- Blå mat gör masken längre, snabbare och ger den en mindre svängradie.
- Gul mat gör masken längre och bredare.
När en boll kolliderar med målet på en spelares planhalva blir motstående spelare tilldelad ett poäng.
Först till en förbestämd mängd mål (standardvärde på 5 mål) vinner.

Vid val av 'Gamemodes' från startmenyn öppnas en meny där många av spelets variabler kan påverkas.
Menyn kan navigeras med 'W' och 'S' eller 'Up' och 'Ner' piltangent.
Värdet på en variabel kan ändras med 'A' och 'D' eller 'Vänster' och 'Höger' piltangent.
Värdet på en variabel kan inte gå under noll.
Det finns ingen övre gräns på värdet som kan ges en variabel men för stora värden kan orsaka problem eller till och med krasher.

Vid val av 'Help' målas en ruta över startmenyn som eventuellt kommer beskriva hur spelet går till och dess kontroller men
för tillfället är det bara en svart låda.

Vid val av 'Exit' avslutas spelet.