# NOR-Urbanc — Razvijanje aplikacij VR/AR

Repozitorij za predmet **Razvijanje aplikacij virtualne in obogatene resničnosti**. Vsa vsebina je v mapi `VR-AR-Predmet/`. GitHub: `https://github.com/matevztasic/NOR.git`. Izvajalec predmeta: Rok Urbanc (GitHub: `TheRokUrbanc`, naj bo dodan kot collaborator — glej spodaj, ni bilo avtomatizirano).

## Projektna ideja

**Vzpon: Zgodba Šoštanjske elektrarne** — VR aplikacija za Meta Quest. Uporabnik pleza po hladilnem stolpu Termoelektrarne Šoštanj (TEŠ), med vzponom se prikazujejo zgodovinske info-točke (1955 začetek gradnje, 1956–1972 rast zmogljivosti, 2015 blok TEŠ 6), na vrhu pa hoja po ploščadi z razgledom in naravno vrtoglavico ob robu.

- Ciljna skupina: šole/energetika, turisti, ljudje s strahom pred višino (izpostavljenostna terapija), zaposleni TEŠ.
- **Tehnologija: WebXR**, ne Unreal Engine (odločitev spremenjena sredi projekta zaradi hitrosti razvoja — glej `vaja-03/tehnicna-zasnova.md`). Nekdanji Unreal Engine C++ skelet je bil izbrisan.

## Struktura repozitorija

```
VR-AR-Predmet/
 ├─ vaja-01/ideja.md              — ideja aplikacije (problem, ciljna skupina, funkcionalnosti)
 ├─ vaja-02/scenes.md + images/   — vizualizacija 3 scen (SVG skice)
 ├─ vaja-03/tehnicna-zasnova.md   — tehnična zasnova: WebXR, Meta Quest, WASD+miška
 ├─ prototype/
 │   ├─ tes-sostanj.html          — GLAVNA DATOTEKA: delujoča interaktivna VR/spletna aplikacija
 │   ├─ README.md
 │   └─ Napake/                   — screenshoti hroščev med razvojem (debug artefakti)
 ├─ final-app/README.md           — načrt za končno oddajo (še ni razvito)
 └─ predstavitev/
     └─ Vzpon-predstavitev.pptx   — PowerPoint po kriterijih za končno predstavitev (glej final-app/README.md)
```

## `predstavitev/Vzpon-predstavitev.pptx`

Zgrajen z `pptxgenjs` (Node) prek ene same skripte, ki NI shranjena v repozitoriju — obstajala je le začasno v seji, ki je datoteko generirala, samo izhodna `.pptx` je trajna. 13 prosojnic, strukturirane po petih kriterijih iz `final-app/README.md` ("Kriteriji za končno predstavitev"): problem/primer uporabe, VR rešitev + funkcionalnosti, tehnologije, delujoča demonstracija, dodana vrednost. Uporablja isto temno paleto barv kot `tes-sostanj.html` (ista `--ink`/`--ember` ipd. iz CSS). Demo prosojnici (8–9) vključujeta prave posnetke zaslona aplikacije (izrisane prek headless Canvas2D, ne mockup skice iz `vaja-02/`). Če se aplikacija spremeni, je treba prosojnico ročno obnoviti — ni avtomatske povezave med kodo in .pptx, skripta za gradnjo pa bi jo bilo treba na novo napisati.

## `tes-sostanj.html` — kako deluje

Samostojna HTML datoteka (brez zunanjih knjižnic/CDN-jev), lasten ročno pisan Canvas2D "3D pogon" s pravo perspektivno projekcijo (ne WebGL/Three.js — namerna odločitev zaradi časovnih omejitev in CSP omejitev artefaktnega okolja).

**Upravljanje:**
- `WASD` — gibanje (ob steni stolpa: W = plezanje navzgor, S = navzdol)
- `Shift` — tek (1.7x hitrost)
- **Pogled z miško, dva načina:** privzeto (brez klika) pozicija kurzorja na zaslonu določa yaw/pitch — enako kot prej. Ob kliku na canvas se poskusi aktivirati **Pointer Lock** (`requestPointerLock`), ki zajame in skrije sistemski kazalec ter uporablja relativne premike (`movementX/Y`) — to prepreči, da bi miška med igro pobegnila na drug monitor ali na opravilno vrstico. Če zaklep ni podprt ali se prekine (Esc/alt-tab, `pointerlockerror`), se aplikacija samodejno in tiho vrne na prejšnji način (mapiranje pozicije) — ni "mrtve točke". Info-panel ob odprtju eksplicitno sprosti zaklep (`exitPointerLock`), da je klikljiv.
- V obeh načinih se surovi vnos miške shrani v `lookTargetYaw/Pitch`, dejanski `player.yaw/pitch` pa se vsako sličico eksponentno glaja proti tarči (`update()`, faktor `1 - Math.exp(-25*dt)`) — to je popravilo pojav, ko je hiter premik miške povzročil, da so se oblaki/hribi (vezani na yaw) na zaslonu "zaleteli" v enem samem frame-u.
- Oblaki imajo poleg paralakse (vezane na yaw) tudi počasen neodvisen premik "vetra" (`drawClouds`, parameter `ts`), da nebo deluje živo tudi, ko igralec stoji pri miru.
- Gumb "O aplikaciji" — predstavitveni panel (problem/rešitev/tehnologije/vrednost)
- Gumb "Ponastavi" — vrne na začetek

**Grafične izboljšave (2026-08-31, druga faza) — kako je dosežen realističen videz:**
- **Osvetlitveni model**: dvočlenski — neposredna sončna komponenta + *hemisferična ambientna* (`shadeForNormal`): ploskve obrnjene navzgor dobijo svetlobo neba, navzdol obrnjene le odboj od tal. Ambientni prag mora ostati visok (~0.40); prenizek prag je bil vzrok, da se je stolp izrisal kot **skoraj črna silhueta**. Dodan `skyMixForNormal` — navzgor obrnjene ploskve prevzamejo hladen odtenek neba.
- **Gladko (Gouraud) senčenje ukrivljenih lupin**: vsaka ploskev stolpa/dimnika nosi `shadeL`/`shadeR` — osvetlitev na svojem **levem in desnem robu**, izračunano iz prave normale pri tistem kotu. Ploskev se zapolni s prelivom med tema vrednostma, zato se sosednji ploskvi ujemata na skupnem robu in faseta izgine. **Ključna podrobnost:** os preliva mora biti pravokotna na *stranske* robove ploskve, ne vzdolž spodnjega roba — pri močni perspektivi stranski rob ni pravokoten na spodnjega, zato barva vzdolž njega zdrsne in šiv ostane (to je bil drugi neuspeli poskus).
- **Nobene naključne variacije na posamezno ploskev** na gladki lupini: karkoli se razlikuje med sosednjima stolpcema, ustvari trd navpičen šiv. Madeži od odtekanja vode (`streakAt`) so zato **zvezna funkcija kota**, vzorčena na robovih ploskve in vgrajena v `shadeL`/`shadeR`, ne barvni odtenek ploskve.
- **Zapiranje antialiasing rež**: Canvas glajenje robov obdela vsak poligon posebej, zato sosednji ploskvi pustita polpikselno svetlo črto. Ploskve z `noEdge` se zato po zapolnitvi še obrobijo v *isti* barvi (`strokeStyle = ctx.fillStyle`).
- **Ni navpičnega preliva na deljenih mrežah**: preliv "svetlo zgoraj / temno spodaj" je namenjen celi steni stavbe; na deljenem stolpu ga vsak obroč ponovi in ustvari trde vodoravne pasove. Zato ga ploskve z `noEdge` preskočijo.
- **Votel stolp z odprtim žrelom (2026-08-31, tretja faza) — dejanska geometrija hladilnega stolpa:**
  - Pravi hladilni stolp s prisilnim vlekom je **votel**: stena TEŠ 6 je debela komaj 18 cm, vrh je odprto žrelo, iz katerega se dviga vodna para. Prej je bil vrh polna plošča — narobe in dolgočasno.
  - Vrh je zdaj **kolobar (galerija)** iz `TOWER_HOLE_R` do `TOWER_RIM_R`, sestavljen iz pasu štirikotnikov, plus notranja stena jaška (`TOWER_INNER_FACES`) z normalami **navznoter** — zato se vidi le *nasprotna* stran jaška, kar je natanko to, kar vidiš, ko pogledaš v pravi stolp.
  - `TOWER_INNER_FACES` je **ločeno polje**: notranjost je vidna šele na robu (`cam.pos.y > TOWER.height - 5`), zato se s tal in med celim vzponom ~112 ploskev sploh ne obdela.
  - **Vrtoglavica velja za oba robova** (zunanji parapet in odprti jašek). `POMEMBNO`: območje padca mora biti **ožje od širine galerije** (0.75 proti galeriji 1.8) — pri prejšnjih 1.6 je bilo širše od celotne poti in vrtoglavica je bila prižgana povsod, tudi na sredini.
  - Ob prihodu z lestve se igralec **postavi na sredino galerije**; sicer pristane na zunanji ustnici, kjer je vrtoglavica takoj polna — nagrada za vzpon je bil temno rdeč tresoč zaslon.
  - **`towerRadiusAt(y)`**: lestev, oprimki in igralčev `z` med plezanjem zdaj sledijo krivini lupine. To je pogoj za izrazitejši stisk (5.4 proti 7.07 ob vznožju); s pritrjeno lestvijo bi ta na sredini višine lebdela metre stran od stene.
  - **Para iz stolpa** (`drawTowerSteam`): 26 prekrivajočih se oblačkov, velikost izračunana iz *svetovnega* polmera skozi projekcijo (zato se steber širi z višino in pravilno manjša z razdaljo), dosleden nagib v veter (kvadratno), skoraj takojšen vzpon motnosti — počasno pojavljanje je puščalo vidno vrzel med robom stolpa in začetkom pare.
  - Dodani **kotlovnica in strojnica** — na fotografijah TEŠ stolp nikoli ne stoji sam.
  - Prikaz višine je usklajen z resnično višino stolpa TEŠ 6 (**164 m**).
  - `POMEMBNO`: morje oblakov je zdaj **omejeno na 0.34** — prej je do vrha naraslo do polne motnosti in pokopalo mesto, jezera in hribe pod belo ploskvijo, s čimer je izgubilo ves smisel vzpona (razgled).

- **Videz Šoštanja / Šaleške doline (namesto generične sivo-bele scene):**
  - `buildAuxFaces` zna zdaj poleg ravne strehe zgraditi **dvokapno streho** (`box.roofH > 0`): dve poševni ploskvi + dva trikotna čela. Streha teče vzdolž daljše stranice. Strma opečnata streha je najbolj prepoznaven znak slovenskega mesta — same ravne škatle berejo kot industrijska cona ne glede na barvo.
  - Razdalja od stolpa določa značaj stavbe: do ~34 enot je še elektrarna (siva, ravna streha, visoka), dlje je mesto (nižje, kremne fasade `HOUSE_WALLS`, opečnate strehe `TILE_ROOFS`).
  - Dodana **župnijska cerkev** (`CHURCH`) — ladja + visok zvonik s sivo konico. To je znak, ki obzorje spremeni iz industrijskega parka v vas.
  - Grebeni hribov so **gozdnati zeleni**, ne sivo skalnati, z visokofrekvenčnim "vrhovi dreves" robom (parameter `rough` v `drawHillLayer`).
  - Velenjsko jezero je **turkizno** (ugrezninsko jezero nad opuščenimi rudniškimi rovi), ne modro.
  - Okna: prej je eno okno prekrivalo ~40 % širine stene → steklena fasada. Zdaj manjša in gostejša, prižganih le ~22 %, ugasla pa **niso črna** — zrcalijo nebo (modrikasta srednja svetlost).
  - **Manj izpiranja**: `POMEMBNO` — megla (`fog*0.66`, stopnja 0.0055), zrno (0.032) in sončni sij (0.13) so bili prej previsoki in so celotno dolino izbelili. Če scena spet postane bela, poglej najprej te tri vrednosti.
- Ostalo: eksponentna (Beer-Lambert) megla namesto linearne, trije grebeni hribov s pravo zračno perspektivo, usmerjene sence (odmaknjene stran od sonca in raztegnjene glede na višino), filmsko zrno (`GRAIN_TILE`, `overlay` pri ~5 %), razsoljena paleta neba, tri različice dreves z osvetljeno stranjo, travnati šopi na fiksni **svetovni** mreži (da ne "plavajo" z igralcem).

**Arhitektura render pogona:**
- Ročna perspektivna projekcija (`toCamera` + `project`), kamera z yaw/pitch iz miške
- Painter's algorithm (risanje od najbolj oddaljenih ploskev proti najbližjim) — sortira se po **najbližji točki ploskve (`minZ`)**, ne po povprečju (`avgZ`) — sprememba je popravila hrošč, kjer so bila okna narisana skozi stolp
- Stolp: hiperboloidna oblika (obročaste ploskve, `TOWER_VIS.rings`), ne škatla
- Dimnik: progast (rdeče-bel), z animiranim dimom
- Stavbe: gradient senčenje (svetel vrh/temna baza), robne linije, mreža oken (nekatera osvetljena) — okna se računajo kot prave 3D točke na steni, projicirane skozi isti pipeline kot vse ostalo
- Oblaki/dim/sij sonca/drevesa: **vnaprej izrisani (pre-rendered) v offscreen canvas sprite ob zagonu**, nato samo `drawImage()` vsako sličico — živ `ctx.filter='blur()'` vsako sličico je bil glavni vzrok zatikanja scene
- Okolica: cesta z vmesno črto, gozd (34+ dreves), 10+ dodatnih stavb, daljnovodni stebri, reka, **Velenjsko jezero** (v daljavi, z obročem dreves), bencinska postaja (nadstrešek na stebrih, trgovinica, 2 črpalki)

## Pomembni popravljeni hrošči (za prihodnje seje)

1. **"Skakajoča okna" / okna "v steni"** — pravi vzrok je bila **eksplozija perspektive**: ko je vogal stene prišel zelo blizu kamere (z < 0.1), se je projekcija matematično napihnila v velikanski lik. Popravek: mejna razdalja dvignjena na 3 enote + dodatna varovalka (če bi bilo okno kljub temu > 180px na zaslonu, se ne nariše). Enak vzorec popravljen tudi pri `drawGroundShadow`.
2. **Depth-sort artefakt** — painter's algorithm s sortiranjem po povprečni (`avgZ`) razdalji ni zanesljiv za velike/raztegnjene oblike (stolp). Popravljeno na sortiranje po najbližji točki (`minZ`).
3. **Zatikanje scene** — glavni vzrok je bil živ `blur()` filter vsako sličico za oblake/dim/sonce. Popravek: vsi ti elementi so zdaj pripravljeni enkrat vnaprej kot sprite (offscreen canvas), nato le prilepljeni.
4. **Plezanje "v" stolp** — kolizijska škatla (`TOWER.halfW/halfD`) je bila manjša od dejanskega (vizualnega) radija hiperboloidnega stolpa. Zdaj je kolizija usklajena z največjim radijem + varnostna razdalja.
5. **Pointer Lock se ni zanesljivo aktiviral** — prvotno v celoti odstranjen, nadomeščen s preprostim mapiranjem pozicije miške na zaslonu → yaw/pitch. Kasneje (2026-08-31) ponovno dodan, tokrat kot izboljšava tega mapiranja, ne zamenjava: zaklep se zdaj sproži izključno na eksplicitni klik na canvas (pravi user-gesture, kar je bil verjetno pravi vzrok prejšnjega tihega neuspeha), z `pointerlockchange`/`pointerlockerror` poslušalci in samodejnim padcem nazaj na mapiranje pozicije, če zaklep ni na voljo — glej razdelek "Upravljanje" zgoraj.
6. **"Noro" poskakovanje oblakov/hribov ob hitrem premiku miške** — `player.yaw` se je prej nastavil takoj na absolutno pozicijo kurzorja, zato je en sam hiter premik miške v enem frame-u premaknil vse od yaw odvisne plasti (oblaki, hribi, jezero) za velik kot naenkrat. Popravek: vnos miške zdaj samo nastavlja tarčo (`lookTargetYaw/Pitch`), dejanski kot pa se vsako sličico eksponentno glaja proti njej (`angleDelta` + `1-Math.exp(-25*dt)` v `update()`).
7. **Drevesa narisana pred stavbami** — drevesa so bila svoj lasten prehod pred `drawBuildings()`, zato je drevo pred stavbo napačno izginilo za njo. Zdaj so vključena v **isti globinsko sortiran prehod** kot poligoni (`kind:'tree'` v polju `visible`).
8. **Lestev/oprimki vidni skozi stolp** — risani so po stolpu, zato so se ob obhodu stolpa videli skozenj. Dodan `ladderVisible()` (velja le s sprednje strani).
9. **Prečka lestve čez cel zaslon med plezanjem** — kamera je le ~0.4 enote od ravnine lestve, zato se je prečka v višini oči projicirala v črto čez celoten zaslon. Prečke bližje od 1.25 enote se med plezanjem preskočijo.
10. **Jezero in drevesa narisani čez "morje oblakov"** — `drawClouds` je tekel pred jezerom/reko. Zdaj teče za njima, oddaljena drevesa pa zbledijo glede na `cloudSeaStrength()`.
11. **Generiranje sten vsako sličico** — `buildAuxFaces()` se je klical v render zanki (≈1000 kratkoživih objektov na sličico → sunkovito delo za zbiralnik smeti). Zdaj `AUX_FACE_CACHE`, zgrajen enkrat.

## Znane omejitve

- Canvas2D pogon, ne pravi WebGL/3D engine — brez pravih tekstur (samo barve + gradienti), brez z-bufferja (painter's algorithm, glej popravke zgoraj — v redkih kombinacijah kotov je še vedno teoretično možen manjši vizualni artefakt pri zelo kompleksnih prekrivanjih).
- Ni prave WebXR immersive-vr seje (ni bilo časa/možnosti testirati na napravi) — aplikacija je "WebXR-track" v smislu tehnološke usmeritve in ker teče v brskalniku brez namestitve, ne dobesedna VR-headset povezava.

## Kaj še manjka

- Ročno dodati `TheRokUrbanc` kot collaborator na GitHub (`github.com/matevztasic/NOR/settings/access`) — ni bilo mogoče avtomatizirati.
- `final-app/` je še prazen načrt — dejanska končna oddaja ob koncu semestra.
- Testiranje na dejanski Meta Quest napravi.
