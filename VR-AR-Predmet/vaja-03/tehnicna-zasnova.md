# Tehnična zasnova aplikacije

Aplikacija: **Vzpon: Zgodba Šoštanjske elektrarne**

## Tip aplikacije
VR

## Uporabnikova prisotnost
**VR – popolna virtualna izkušnja.**
Uporabnik je v celoti potopljen v virtualno okolje termoelektrarne. Popolna izolacija od realnega okolja je nujna, saj je jedro doživetja odvisno od prepričljivega občutka višine, vrtoglavice in fizičnega plezanja – učinkov, ki jih z obogateno resničnostjo (AR) ne bi bilo mogoče verodostojno doseči.

## Razvojno orodje
**Unreal Engine (UE).**
Odločitev sledi priporočilu, saj smo se z UE že seznanili v 1. semestru. Poleg tega UE ponuja:
- zmogljiv sistem osvetlitve in materialov (Lumen, Nanite), primeren za realističen prikaz betonske/kovinske industrijske konstrukcije,
- vgrajen VR predlogo (VR Template) in sistem Enhanced Input, primeren za implementacijo plezalne mehanike s kontrolerji,
- dobro podporo za Meta Quest preko OpenXR vtičnika.

## Ciljna naprava
**VR očala – Meta Quest** (samostojna naprava, brez potrebe po dodatnem računalniku). Taka izbira omogoča uporabo aplikacije tudi izven laboratorija, npr. na terenu, v šoli ali v morebitnem obiskovalnem centru TEŠ.

## Način interakcije
- **VR kontrolerji** – primarni način interakcije, uporabljen za plezalno mehaniko (prijemanje in premikanje po oprijemih).
- **Pogled** – uporablja se za sprožanje prikaza zgodovinskih informacijskih tabel med vzponom ter za zaznavo približevanja robu ploščadi na vrhu (učinek vrtoglavice).
