# Končna aplikacija – Vzpon: Zgodba Šoštanjske elektrarne

Ta mapa je namenjena končni, delujoči različici VR aplikacije, oddani ob zaključku semestra, ki nadgradi `/prototype/` v celovito izkušnjo, pripravljeno za predstavitev.

## Kaj končna aplikacija doda glede na prototip
- **Celoten vzpon**, ne le ena testna stena – več segmentov konstrukcije z naraščajočo težavnostjo.
- **Vse zgodovinske info-točke** (vsaj 4–5), ki skupaj povedo zgodbo TEŠ od gradnje (1955) do danes, vključno z arhivskimi fotografijami/zvokom.
- **Dodelan sistem napredka** – HUD s prikazom višine, deležem opravljenega vzpona, sistem "checkpointov" (varnostnih točk, kamor se uporabnik lahko vrne po padcu prijema).
- **Dodelan učinek vrtoglavice na vrhu** – kombinacija vizualnih (zamegljen rob pogleda, tresenje), zvočnih (veter) in prostorskih (globinska meglica) elementov.
- **Zvočna in glasbena podlaga**, osnovni UI za začetni meni (izbira "začni vzpon", nastavitve udobja/comfort options za VR – npr. vinjetiranje proti slabosti).
- **Optimizacija in testiranje na napravi** (stabilne sličice/s na Meta Quest).

## Struktura oddaje
```
final-app/
 ├─ VzponTES/              (kompleten Unreal Engine .uproject, glej strukturo iz /prototype/)
 ├─ Builds/                (izvožen .apk build za Meta Quest, ni nujno v Gitu zaradi velikosti - glej opombo spodaj)
 └─ demo/                  (posnetek zaslona/videa demonstracije delovanja, npr. demo.mp4 ali povezava)
```

> Opomba: velike binarne datoteke (izvoženi `.apk`, video posnetki) naj se, če presegajo GitHub omejitve, povežejo prek zunanje povezave (npr. Google Drive) v tem README-ju, namesto da se commitajo neposredno.

## Kriteriji za končno predstavitev (iz navodil predmeta)
Pri predstavitvi je treba pokazati:
1. problem oziroma primer uporabe (dostopnost visokih industrijskih objektov + izobraževanje o zgodovini TEŠ),
2. VR rešitev in ključne funkcionalnosti (plezanje, zgodovinske točke, vrh + vrtoglavica),
3. uporabljene tehnologije (Unreal Engine, Meta Quest, OpenXR),
4. delujočo demonstracijo aplikacije v živo ali prek posnetka,
5. dodano vrednost rešitve (varno doživetje sicer nedostopnega prostora + izobraževalna vsebina + morebitna uporaba pri izpostavljenosti strahu pred višino).

## Status
Vsebina te mape bo dodana ob zaključku projektnega dela, po zaključenem razvoju v `/prototype/`.
