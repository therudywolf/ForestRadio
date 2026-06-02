# 🐺 ForestRadio

**Кастомная прошивка Quansheng UV-K5 / K6 / 5R — «кибердека в мире радио».**
Заточена под радиосталкинг, скрытную связь на 2–3 рации и маскировку в эфире.

Custom firmware for the Quansheng UV-K5 / K6 / 5R focused on band sweeping &
signal hunting, low-profile small-group comms, and on-air stealth.

> Проект мой (therudywolf), но стоит на плечах гигантов — см. [родословную](#родословная--lineage).
> Это **форк**, идущий своим путём; PR в upstream не планируется (автор забросил проект).

---

## ⚠️ Дисклеймер

У ЭТОЙ ПРОШИВКИ НЕТ МОЗГА — ПОЛЬЗУЙСЯ СВОИМ. Заливаешь на свой страх и риск:
она может не работать, может **закирпичить** рацию. Перед заливкой **сделай бэкап
EEPROM** ([k5prog](https://github.com/sq5bpf/k5prog)). Фичи, затрагивающие передачу,
скремблер и мощность, используются **под твою ответственность** и в рамках местного
законодательства (в РФ без лицензии: PMR-446 ≤0.5 Вт, LPD-433 ≤10 мВт).

This firmware has no brain — use your own. Flash at your own risk; it can brick your
radio. Back up your EEPROM first. Transmit/scrambler/power features are used under
your own responsibility and applicable law.

---

## Что это даёт

Сборка «лин»: минимум настроек, оптимальные дефолты захардкожены, всё лишнее вырезано
ради места под фичи. Три опоры:

- 🔍 **Сталкинг** — широкий приём, скан диапазонами, чувствительный шумодав, AM-fix,
  спектроанализатор с гибридным детектором (не залипает на помехах).
- 👥 **Связь на 2–3** — двойной/тройной вотч, преднабор каналов PMR-446 / LPD-433,
  быстрый сбор группы.
- 🥷 **Маскировка** — аналоговый скремблер, «немой» TX (только несущая), рандом частоты,
  тихий маяк, низкая мощность, режим-обманка «Гражданка» (рация прикидывается обычной
  8-канальной walkie).

### Статус фич

| | Фича | Статус |
|---|---|---|
| E1 | Гибридный спектр (RSSI + шум + глитч) | ✅ в сборке (пороги тюнятся на железе) |
| 🐺 | Волчий boot-логотип + позывной | ✅ в сборке |
| — | Лин-профиль сборки под МСК | ✅ в сборке |
| E3 | Аналоговый скремблер (инверсия) | 🚧 в работе |
| E4 | «Немой» TX (carrier-only) | 🚧 в работе |
| E13 | Лут пойманной частоты в канал | 🚧 в работе |
| E2 | Режим X + лут-буфер (фоновый перехват) | 🚧 в плане |
| E7 | Тройной вотч | 🚧 в плане |
| E5 / E14 | Рандом частоты / тихий маяк | 🚧 в плане |
| E12 | Турбо-скан с авто-блеклистом помех | 🚧 в плане |
| E16 | Преднабор каналов PMR-446 / LPD-433 | 🚧 в плане |
| E18 | «Гражданка» (decoy / аутист-мод) | 🚧 в плане |
| E9 / E15 | Киберпанк-шрифт / роджер | 🚧 в плане |

Полный план и выбор опций — в [`ForestRadio.md`](ForestRadio.md) и
[`ForestRadio.xlsx`](ForestRadio.xlsx).

---

## Сборка / Building

Тулчейн `arm-none-eabi-gcc` не обязателен — собираем в Docker.

```bash
# образ собирается один раз
docker build -t uvk5 .

# сборка (живые исходники монтируются, артефакты игнорятся git)
docker run --rm -v "$PWD:/app" -w /app uvk5 bash -c "make clean && make"
# → f4hwn.packed.bin   (заливать через https://egzumer.github.io/uvtools)
```

Опции сборки — в [`Makefile`](Makefile) (флаги `ENABLE_*`). Готовые бинарники — в
[`compiled-firmware/`](compiled-firmware).

---

## Родословная / Lineage

ForestRadio — форк по цепочке. Спасибо авторам, без них ничего бы не было:

- [DualTachyon](https://github.com/DualTachyon/uv-k5-firmware) — оригинальная открытая прошивка
- [fagci](https://github.com/fagci) — спектроанализатор
- [OneOfEleven](https://github.com/OneOfEleven/uv-k5-firmware-custom) — большой набор модов
- [Egzumer](https://github.com/egzumer/uv-k5-firmware-custom) — объединение и развитие
- [F4HWN / armel](https://github.com/armel/uv-k5-firmware-custom) — редакции, UI, оптимизации
- **ForestRadio** ([therudywolf](https://github.com/therudywolf)) — этот форк

Авторские копирайты в исходниках сохранены. Лицензия — Apache 2.0.

---

## License

Copyright 2023 Dual Tachyon and contributors; ForestRadio changes © therudywolf.

Licensed under the Apache License, Version 2.0. You may obtain a copy at
<http://www.apache.org/licenses/LICENSE-2.0>. Distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See [`LICENSE`](LICENSE).
