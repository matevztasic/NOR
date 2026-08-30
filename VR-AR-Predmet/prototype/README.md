# Prototip – Vzpon: Zgodba Šoštanjske elektrarne

`tes-sostanj.html` je delujoča **WebXR/spletna aplikacija** (brez zunanjih knjižnic, samostojna datoteka) — teče neposredno v brskalniku, brez namestitve. Implementira jedrno mehaniko iz `/vaja-01/` (ideja) in `/vaja-02/` (scene) v pravem prvoosebnem 3D okolju:

- **Prosta hoja okoli elektrarne** – WASD gibanje, klik + vleci za pogled (miška), z realnim razgledom po okolici TEŠ (glavni stolp, stranske stavbe, dolina, gorovje v ozadju).
- **Plezanje** – pristop k steni stolpa in vlečenje navzgor (drži W ob steni).
- **Zgodovinske info-točke** – prikažejo se ob določenih višinah med vzponom.
- **Hoja po vrhu ploščadi** – prosto gibanje po vrhu, pogled navzdol na dolino, bližina roba naravno sproži učinek vrtoglavice (vinjeta, tresenje, opozorilo).

## Zagon
Samo odprite `tes-sostanj.html` v poljubnem brskalniku (dvoklik, ali Chrome/Edge → Datoteka → Odpri) — ni potrebna nobena namestitev.

## Upravljanje
- **W A S D** – gibanje (ob steni: W za plezanje navzgor, S navzdol)
- **Klik + vleci z miško** – pogled okoli
- Gumb **"O aplikaciji"** – odpre predstavitveni panel (problem, rešitev, funkcionalnosti, tehnologije, dodana vrednost)
- Gumb **"Ponastavi"** – vrne na začetek

## Zakaj WebXR namesto Unreal Engine
Glej `/vaja-03/tehnicna-zasnova.md` — odločitev temelji na hitrosti razvoja (takojšen zagon brez gradbenega procesa) in neposredni združljivosti z brskalnikom naprave Meta Quest.
