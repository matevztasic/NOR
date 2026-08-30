# Prototip – Vzpon: Zgodba Šoštanjske elektrarne

Mapa `VzponTES/` vsebuje **pravo Unreal Engine C++ ogrodje** (ne le načrt): `.uproject`, gradbene datoteke in 4 delujoče C++ razrede, ki implementirajo jedrno mehaniko iz `/vaja-01/` (ideja) in `/vaja-02/` (scene):

- `AVzponClimbingCharacter` – VR igralec s plezalno mehaniko (Source/VzponTES/ClimbingCharacter.h/.cpp)
- `AClimbHold` – oprijem na steni (ClimbHold.h/.cpp)
- `AHistoryInfoPanel` – zgodovinska info-točka (HistoryInfoPanel.h/.cpp)
- `AVertigoZone` – učinek vrtoglavice na vrhu (VertigoZone.h/.cpp)

**To kodo je treba enkrat postaviti v Unreal Editorju** (namestitev meshov/materialov/zvokov, Blueprint podrazredi, Enhanced Input assetje) – to je ročno grafično delo, ki ga ni mogoče avtomatizirati. Natančna navodila korak-za-korak so v [`VzponTES/SETUP.md`](VzponTES/SETUP.md).

## Cilj prototipa (MVP)
Prototip mora dokazati tri jedrne mehanike iz zasnove, ne še celotne aplikacije:
1. **Plezanje** – uporabnik se z VR kontrolerji prime in premakne po vsaj eni steni z oprijemi.
2. **Ena zgodovinska info-točka** – ob približevanju/pogledu na označeno mesto se prikaže plavajoča tabla z besedilom/sliko (glej Scena 2 v `/vaja-02/scenes.md`).
3. **Prihod na vrh + učinek višine** – uporabnik doseže ploščad, lahko po njej hodi, sproži se vizualni/zvočni efekt vrtoglavice (glej Scena 3).

## Struktura UE projekta
```
prototype/
 └─ VzponTES/
     ├─ VzponTES.uproject
     ├─ SETUP.md                       (navodila za namestitev in zagon)
     ├─ Config/
     │   ├─ DefaultEngine.ini
     │   └─ DefaultGame.ini
     ├─ Source/
     │   ├─ VzponTES.Target.cs
     │   ├─ VzponTESEditor.Target.cs
     │   └─ VzponTES/
     │       ├─ VzponTES.Build.cs
     │       ├─ ClimbingCharacter.h/.cpp    (plezalna mehanika)
     │       ├─ ClimbHold.h/.cpp            (oprijem na steni)
     │       ├─ HistoryInfoPanel.h/.cpp     (zgodovinska info-točka)
     │       └─ VertigoZone.h/.cpp          (učinek vrtoglavice na vrhu)
     └─ Content/                       (nastane v Editorju: nivo, Blueprinti, meshi, materiali, UMG)
```

## Mejniki razvoja
| Faza | Vsebina | Status |
|---|---|---|
| 1 | Namestitev UE, prazen VR template projekt zažene se na Quest | ⬜ |
| 2 | Osnovna scena: stolp (blockout mesh) + prosto premikanje | ⬜ |
| 3 | Plezalna mehanika (grab & climb) na testni steni | ⬜ |
| 4 | Ena interaktivna zgodovinska info-točka | ⬜ |
| 5 | Ploščad na vrhu + učinek vrtoglavice | ⬜ |
| 6 | Testiranje na napravi (Meta Quest) in popravki | ⬜ |

## Ciljna naprava za testiranje
Meta Quest (prek Meta XR/OpenXR plugina in Quest Link ali samostojni build za Android/Quest).
