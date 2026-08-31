# Prototip – Vzpon: Zgodba Šoštanjske elektrarne

`tes-sostanj.html` je delujoča **WebXR/spletna aplikacija** (brez zunanjih knjižnic, samostojna datoteka) — teče neposredno v brskalniku, brez namestitve. Implementira jedrno mehaniko iz `/vaja-01/` (ideja) in `/vaja-02/` (scene) v pravem prvoosebnem 3D okolju:

- **Prosta hoja okoli elektrarne** – WASD gibanje, pogled z miško (privzeto: pozicija kurzorja; ob kliku na platno se aktivira zaklep miške za FPS-slog gledanja), z realnim razgledom po okolici TEŠ (hladilni stolp, dimnik, kotlovnica, mesto Šoštanj, dolina, gorovje v ozadju).
- **Plezanje** – pristop k steni stolpa in vlečenje navzgor (drži W ob steni); lestev sledi ukrivljeni hiperboloidni obliki lupine.
- **Zgodovinske info-točke** – prikažejo se ob določenih višinah med vzponom.
- **Votel vrh z odprtim žrelom** – hoja po galeriji okoli odprtine (pravi hladilni stolp je votel), para se dviga iz jaška; bližina obeh robov (zunanji rob in odprti jašek) naravno sproži učinek vrtoglavice (vinjeta, tresenje, opozorilo).

## Zagon
Samo odprite `tes-sostanj.html` v poljubnem brskalniku (dvoklik, ali Chrome/Edge → Datoteka → Odpri) — ni potrebna nobena namestitev.

## Upravljanje
- **W A S D** – gibanje (ob steni: W za plezanje navzgor, S navzdol)
- **Shift** – tek
- **Miška** – pogled okoli (privzeto brez klika; klik na platno zaklene kurzor za FPS-slog gledanja, Esc sprosti)
- Gumb **"O aplikaciji"** – odpre predstavitveni panel (problem, rešitev, funkcionalnosti, tehnologije, dodana vrednost)
- Gumb **"Ponastavi"** – vrne na začetek

## Zakaj WebXR namesto Unreal Engine
Glej `/vaja-03/tehnicna-zasnova.md` — odločitev temelji na hitrosti razvoja (takojšen zagon brez gradbenega procesa) in neposredni združljivosti z brskalnikom naprave Meta Quest.
