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
 └─ final-app/README.md           — načrt za končno oddajo (še ni razvito)
```

## `tes-sostanj.html` — kako deluje

Samostojna HTML datoteka (brez zunanjih knjižnic/CDN-jev), lasten ročno pisan Canvas2D "3D pogon" s pravo perspektivno projekcijo (ne WebGL/Three.js — namerna odločitev zaradi časovnih omejitev in CSP omejitev artefaktnega okolja).

**Upravljanje:**
- `WASD` — gibanje (ob steni stolpa: W = plezanje navzgor, S = navzdol)
- `Shift` — tek (1.7x hitrost)
- **Premikanje miške po zaslonu neposredno določa smer pogleda** (brez klika!) — pozicija kurzorja se mapira na yaw/pitch. To je bilo namenoma spremenjeno iz Pointer Lock API-ja, ker se ta v uporabnikovem okolju ni zanesljivo aktiviral (tiho ni deloval, brez napake).
- Gumb "O aplikaciji" — predstavitveni panel (problem/rešitev/tehnologije/vrednost)
- Gumb "Ponastavi" — vrne na začetek

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
5. **Pointer Lock se ni zanesljivo aktiviral** — v celoti odstranjen, nadomeščen s preprostim mapiranjem pozicije miške na zaslonu → yaw/pitch (brez potrebe po posebnem brskalniškem dovoljenju).

## Znane omejitve

- Canvas2D pogon, ne pravi WebGL/3D engine — brez pravih tekstur (samo barve + gradienti), brez z-bufferja (painter's algorithm, glej popravke zgoraj — v redkih kombinacijah kotov je še vedno teoretično možen manjši vizualni artefakt pri zelo kompleksnih prekrivanjih).
- Ni prave WebXR immersive-vr seje (ni bilo časa/možnosti testirati na napravi) — aplikacija je "WebXR-track" v smislu tehnološke usmeritve in ker teče v brskalniku brez namestitve, ne dobesedna VR-headset povezava.

## Kaj še manjka

- Ročno dodati `TheRokUrbanc` kot collaborator na GitHub (`github.com/matevztasic/NOR/settings/access`) — ni bilo mogoče avtomatizirati.
- `final-app/` je še prazen načrt — dejanska končna oddaja ob koncu semestra.
- Testiranje na dejanski Meta Quest napravi.
