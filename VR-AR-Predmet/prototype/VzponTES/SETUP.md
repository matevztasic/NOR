# Navodila za zagon prototipa

V tej mapi je **pravo Unreal Engine C++ ogrodje** (ne le načrt): `.uproject`, gradbene datoteke in 4 C++ razredi, ki implementirajo jedrno mehaniko iz `/vaja-01/` in `/vaja-02/`:

- `AVzponClimbingCharacter` – VR igralec s plezalno mehaniko (hand-over-hand, prijemanje z motion kontrolerji).
- `AClimbHold` – posamezen oprijem na steni.
- `AHistoryInfoPanel` – zgodovinska info-točka, ki se prikaže ob približevanju.
- `AVertigoZone` – cona na vrhu, ki sproži vizualni/zvočni učinek vrtoglavice.

Tega koraka ni mogoče avtomatizirati brez odprtega Unreal Editorja – spodaj so točni koraki, da to enkrat postavite sami (kasneje samo prevajate/testirate).

## 1. Namestitev Unreal Engine
1. Namestite **Epic Games Launcher**: https://store.epicgames.com/download (potreben brezplačen Epic račun).
2. V launcherju: zavihek **Unreal Engine → Library → +** in namestite **verzijo 5.4** (ali novejšo – če namestite drugo verzijo, popravite `"EngineAssociation"` v `VzponTES.uproject`).
3. Namestite tudi **Visual Studio 2022** z delovno obremenitvijo **"Game development with C++"** (potrebno za prevajanje C++ kode) – Unreal Editor vas na to opozori, če manjka.

## 2. Odpiranje tega projekta
1. V Raziskovalcu poiščite `VzponTES.uproject` v tej mapi.
2. Z desnim klikom nanj izberite **Generate Visual Studio project files** (Unreal to doda v kontekstni meni ob namestitvi).
3. Odprite nastalo `VzponTES.sln` v Visual Studiu, izberite konfiguracijo **Development Editor**, in zaženite **Build** (Ctrl+Shift+B).
4. Ko prevajanje uspe, dvokliknite `VzponTES.uproject` – odprl se bo Unreal Editor.

## 3. Kar morate narediti v Editorju (enkratna postavitev)
Spodnje je ročno delo v grafičnem vmesniku, ki ga sam ne morem opraviti:

1. **Nivo**: ustvarite nov nivo `Content/Maps/TowerPrototype` (ujema se z `DefaultEngine.ini`).
2. **Enhanced Input**: ustvarite `IMC_VR` (Input Mapping Context) ter `IA_GripLeft`/`IA_GripRight` (Input Action, tip Digital/bool), vezane na Motion Controller (L)/(R) Trigger ali Grip vhode.
3. **BP_ClimbingCharacter**: Blueprint podrazred `AVzponClimbingCharacter`, v defaultih nastavite `VRMappingContext`, `GripLeftAction`, `GripRightAction`. V **Project Settings → Maps & Modes** ga nastavite kot **Default Pawn Class**.
4. **BP_ClimbHold**: Blueprint podrazred `AClimbHold`, dodelite `HoldMesh` (npr. preprosta kocka/oblika iz Starter Content) in ga postavite večkrat vzdolž stene v nivoju.
5. **WBP_HistoryPanel**: UMG Widget Blueprint s tekstovnima poljema (naslov/opis) in sliko. **BP_HistoryInfoPanel** (podrazred `AHistoryInfoPanel`) mu nastavite `InfoWidget → Widget Class`, nato v level postavite instance in vsaki izpolnite `Title`/`Description`/`HistoricalImage`.
6. **BP_VertigoZone**: Blueprint podrazred `AVertigoZone`, dodelite `WindLoopSound` (zvok vetra iz Content Browserja/Marketplace), postavite ob robu ploščadi na vrhu.
7. Zaženite v VR predogledu (**Play → VR Preview**, s priključenim Meta Quest prek Quest Link/Air Link) in preverite plezanje, info-točko ter vrtoglavico.

## Znane omejitve tega ogrodja
- Plezalna mehanika je osnovna (`Tick`-based hand-over-hand); ne obravnava kolizij s steno med vlekom, kar je smiselno dodati kasneje (npr. sweep/collision test pred `AddActorWorldOffset`).
- 3D modeli, materiali in zvoki niso vključeni – to je umetniško/vsebinsko delo, ki ga naredite v Editorju ali uvozite (Quixel Bridge, Marketplace).
- `MetaXR` plugin je v `.uproject` naveden kot izklopljen – če boste ciljali izključno na Meta Quest z Meta XR SDK namesto generičnega OpenXR, ga vklopite (potrebna dodatna namestitev vtičnika iz Meta Quest Developer Hub).
