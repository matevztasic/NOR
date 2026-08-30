# Tehnična zasnova aplikacije

Aplikacija: **Vzpon: Zgodba Šoštanjske elektrarne**

## Tip aplikacije
VR

## Uporabnikova prisotnost
**VR – popolna virtualna izkušnja.**
Uporabnik je v celoti potopljen v virtualno okolje termoelektrarne. Popolna izolacija od realnega okolja je nujna, saj je jedro doživetja odvisno od prepričljivega občutka višine, vrtoglavice in fizičnega plezanja – učinkov, ki jih z obogateno resničnostjo (AR) ne bi bilo mogoče verodostojno doseči.

## Razvojno orodje
**WebXR (spletna VR aplikacija).**
Odločitev za WebXR namesto Unreal Engine temelji na hitrosti razvoja in dostopnosti:
- aplikacija teče neposredno v brskalniku, brez namestitve ali gradbenega procesa – vsaka sprememba je takoj vidna in preizkusljiva,
- WebXR Device API omogoča neposreden zagon v brskalniku naprave Meta Quest, brez ločenega paketiranja aplikacije,
- za zgodnjo fazo razvoja in pogosto iteriranje (kot pri tem projektu) je hitrost preizkušanja pomembnejša od naprednejših grafičnih zmogljivosti namenskega pogona.

## Ciljna naprava
**VR očala – Meta Quest** (samostojna naprava, brez potrebe po dodatnem računalniku). Taka izbira omogoča uporabo aplikacije tudi izven laboratorija, npr. na terenu, v šoli ali v morebitnem obiskovalnem centru TEŠ.

## Način interakcije
- **VR kontrolerji / hoja** – primarni način gibanja in plezanja (v namizni razvojni različici: tipke WASD za gibanje, miška za pogled).
- **Pogled in bližina** – sprožata prikaz zgodovinskih informacijskih tabel med vzponom ter zaznavo približevanja robu ploščadi na vrhu (učinek vrtoglavice).
