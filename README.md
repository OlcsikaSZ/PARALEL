# Game of Life - Párhuzamos implementációk

Ez a projekt a Conway-féle **Game of Life** párhuzamos implementációját tartalmazza három különböző technológia segítségével:
- **pthread**
- **OpenMP**
- **CUDA**

A feladat célja a különböző párhuzamos technológiák alkalmazása és a futásidő optimalizálása. Az implementációk célja, hogy összehasonlítsák a különböző párhuzamosítási megoldások teljesítményét és hatékonyságát különböző probléma méreteken és számítási egységek számánál.

## Feladat specifikációja

A Conway-féle **Game of Life** egy cella alapú szimuláció, amelyben minden egyes cella két állapotban létezhet: élő vagy halott. A játéknak az alábbi szabályai vannak:
1. Minden élő cellának pontosan két vagy három élő szomszédja kell, hogy legyen, különben meghal.
2. Minden halott cellának pontosan három élő szomszédja kell, hogy legyen, hogy életre keljen.

A feladat a játéknak ezt a logikáját különböző párhuzamos technológiákkal (pthread, OpenMP, CUDA) implementálja, és a futásidőt mérve vizsgálja a különböző technológiai megoldások hatékonyságát.

## Alkalmazott technológiák

1. **pthread**: A **pthread** könyvtár segítségével szálakat indítunk, ahol a grid különböző részeit dolgozzák fel a szálak párhuzamosan. A feladatot különböző számú szállal párhuzamosítjuk, és mérjük a futásidőt.

2. **OpenMP**: Az **OpenMP** direktíváival párhuzamosítjuk a kétdimenziós grid feldolgozását. A `#pragma omp parallel for collapse(2)` direktíva segítségével egyszerűsítjük a párhuzamosítást.

3. **CUDA**: A **CUDA** segítségével a számításokat a GPU-n végezzük, ezzel jelentősen felgyorsítva a feldolgozást a szálak párhuzamos futtatásával. A **CUDA kernel** végzi a grid egyes elemeinek kiszámítását párhuzamosan.

## Tervezett futtatások és mérések

A projekt célja, hogy mérje és összehasonlítsa a futásidőt a különböző implementációk esetében. A következő teszteket végezzük el:

1. **Probléma méret növelésével kapcsolatos futásidő mérés**:
    - Különböző grid méretekkel (pl. 100x100, 500x500, 1000x1000) mérjük a futásidőt minden párhuzamos technológia esetében.
    - A futásidő változását ábrázoljuk különböző problémaméretek mellett.

2. **Szálak számának növelésével kapcsolatos futásidő mérés**:
    - Különböző számú szál használatával (pl. 1, 2, 4, 8 szál) mérjük a futásidőt egy adott probléma méret mellett.
    - A futásidő változását ábrázoljuk különböző szálak számánál.

A mért adatokat és grafikonokat PDF formátumban, a **README.md** fájl mellékleteként csatoljuk.

## A projekt futtatása

### Előfeltételek
- **pthread**: A pthread könyvtár használatát nem szükséges telepíteni, mivel alapértelmezetten elérhető a legtöbb Linux disztribúcióban.
- **OpenMP**: Az OpenMP könyvtár szintén alapértelmezetten elérhető a modern C fordítókban (pl. GCC).
- **CUDA**: A CUDA használatához telepíteni kell a **NVIDIA CUDA Toolkit**-et, valamint a megfelelő GPU-t.

### Futtatás

1. **pthread verzió futtatása**:
    - A pthread verzió elindításához egyszerűen fordítsd le a kódot és futtasd a következő parancsokkal:
    ```bash
    gcc -o gol_pthread gol.c -lpthread
    ./gol_pthread
    ```

2. **OpenMP verzió futtatása**:
    - Az OpenMP verzió elindításához használd a következő parancsokat:
    ```bash
    gcc -o gol_openmp gol.c -fopenmp
    ./gol_openmp
    ```

3. **CUDA verzió futtatása**:
    - A CUDA verzió elindításához szükséges a CUDA Toolkit telepítése, majd a kód fordítása és futtatása:
    ```bash
    nvcc -o gol_cuda gol.cu
    ./gol_cuda
    ```

### Mérések

A program futtatása során mérjük a különböző implementációk futásidejét különböző problémaméretek és számítási egységek számának mellett. Az eredményeket grafikonokon ábrázoljuk, és azokat a projekt dokumentációjában elemezzük.

## Eredmények és elemzés

A program futásának mérésével és az eredmények összehasonlításával azt vizsgáljuk, hogy a különböző párhuzamos technológiák hogyan befolyásolják a **Game of Life** szimuláció futásidejét. Az OpenMP és pthread verziók esetében a szálak számának növelésével mérhetjük a futásidőt, míg a CUDA esetében a GPU teljesítményét és a szálak számát is teszteljük.

### Grafikonok

- **Futásidő változása problémaméret növelésével**:
    - Grafikonok, amelyek megmutatják, hogyan nő a futásidő a grid méretének növelésével.
  
- **Futásidő változása szálak számának növelésével**:
    - Grafikonok, amelyek a szálak számának növelésével ábrázolják a futásidő csökkenését.

## License

A projekt **MIT License** alatt van licencelve. További információt a [LICENSE](LICENSE) fájlban találhatsz.