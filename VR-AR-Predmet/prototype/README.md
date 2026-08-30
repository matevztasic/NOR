# Prototip – Vzpon: Zgodba Šoštanjske elektrarne

Ta mapa je namenjena delujočemu VR prototipu (MVP), ki dokaže osrednjo mehaniko aplikacije iz `/vaja-01/` (ideja), `/vaja-02/` (scene) in `/vaja-03/` (tehnična zasnova). Prava vsebina Unreal Engine projekta (`.uproject`, `.uasset`, blueprinti, mape) nastane šele v UE Editorju – ta dokument je načrt/ogrodje, po katerem se razvoj izvede.

## Kako dobiti Unreal Engine
1. Prenesi in namesti **Epic Games Launcher**: https://store.epicgames.com/download (potreben brezplačen Epic Games račun).
2. V launcherju odpri zavihek **Unreal Engine → Library** in klikni **+** za namestitev najnovejše LTS različice (priporočeno UE 5.4 ali novejša).
3. Po namestitvi v launcherju izberi **Games → New Project → Virtual Reality template** (ali *Blank* + dodaš OpenXR/Meta XR plugin), poimenuj projekt npr. `VzponTES` in ga ustvari **znotraj te mape** (`/prototype/`), da bo `.uproject` del repozitorija.

## Cilj prototipa (MVP)
Prototip mora dokazati tri jedrne mehanike iz zasnove, ne še celotne aplikacije:
1. **Plezanje** – uporabnik se z VR kontrolerji prime in premakne po vsaj eni steni z oprijemi.
2. **Ena zgodovinska info-točka** – ob približevanju/pogledu na označeno mesto se prikaže plavajoča tabla z besedilom/sliko (glej Scena 2 v `/vaja-02/scenes.md`).
3. **Prihod na vrh + učinek višine** – uporabnik doseže ploščad, lahko po njej hodi, sproži se vizualni/zvočni efekt vrtoglavice (glej Scena 3).

## Načrtovana struktura UE projekta
```
prototype/
 └─ VzponTES/                     (Unreal Engine .uproject)
     ├─ VzponTES.uproject
     ├─ Config/
     ├─ Content/
     │   ├─ Maps/
     │   │   └─ TowerPrototype.umap
     │   ├─ Blueprints/
     │   │   ├─ BP_ClimbHold.uasset        (posamezen oprijem, zazna prijem roke)
     │   │   ├─ BP_ClimbingCharacter.uasset (plezalna gibalna logika)
     │   │   ├─ BP_HistoryInfoPanel.uasset  (prikaz zgodovinske vsebine)
     │   │   ├─ BP_TopPlatform.uasset       (ploščad + trigger za vrtoglavico)
     │   │   └─ BP_VertigoEffect.uasset     (post-process učinek višine)
     │   ├─ Meshes/         (dimnik/stolp, oprijemi, ploščad – lahko iz Quixel/Marketplace)
     │   ├─ Materials/      (beton, kovina, nebo)
     │   └─ UI/             (HUD napredka, opozorilo o višini)
     └─ Source/             (če se doda C++ logika, sicer samo Blueprinti)
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
