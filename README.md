# ESP32 Blink 範例 (PlatformIO)

第一個 ESP32 程式：讓板子上的 LED 閃爍。本專案使用 **PlatformIO** 建置。

---

## 環境需求

- [VS Code](https://code.visualstudio.com/) 或 [Cursor](https://cursor.sh/)
- [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) 擴充套件（安裝後會自動安裝 PlatformIO Core 與 ESP32 平台）

**不需**另外安裝 ESP-IDF 或執行 `activate-idf` 等腳本，PlatformIO 會自動管理工具鏈。

---

## 硬體

- **內建 LED**：多數 ESP32 開發板上的小 LED 接在 **GPIO 2**。燒錄後應會每 0.5 秒閃一次。
- 若你的板子 LED 接在不同腳位，請在 `src/main.c` 裡修改 `#define BLINK_GPIO 2` 的數字。

---

## 一、編譯（Build）

在專案目錄開啟終端機（或 VS Code / Cursor 內建終端機），執行：

```bash
pio run
```

或使用完整指令：

```bash
platformio run
```

成功後會出現 `SUCCESS`，編譯產物在 `.pio/build/` 下。

### 指定板子（多環境時）

若在 `platformio.ini` 中啟用了多個 `[env:xxx]`，可指定環境編譯，例如：

```bash
pio run -e esp32dev
```

---

## 二、燒錄（Flash）

1. 用 **USB 線** 將 ESP32 接到電腦。
2. 若電腦認不到板子，請安裝 **CP210x** 或 **CH340** 驅動（依板子型號）。
3. 在裝置管理員確認 **COM 埠號**（例如 `COM3`）。

在專案目錄執行：

```bash
pio run -t upload
```

指定 COM 埠（若自動偵測不到時）：

```bash
pio run -t upload --upload-port COM3
```

燒錄成功後板子會重啟，LED 開始閃爍。

---

## 三、一次完成：編譯 + 燒錄

```bash
pio run -t upload
```

指定埠號：

```bash
pio run -t upload --upload-port COM3
```

---

## 四、序列埠監控（Monitor）

查看程式輸出的 log（例如 "LED ON" / "LED OFF"）：

```bash
pio device monitor
```

指定埠號與鮑率：

```bash
pio device monitor -p COM3 -b 115200
```

按 `Ctrl+C` 可結束 monitor。

---

## 五、在 VS Code / Cursor 中使用

1. 用 **「開啟資料夾」** 開啟本專案根目錄。
2. 確認已安裝 **PlatformIO IDE** 擴充套件。
3. 下方狀態列會出現 PlatformIO 圖示，可點選：
   - **Build**：編譯  
   - **Upload**：燒錄  
   - **Serial Monitor**：序列監控  
4. 或使用快捷鍵 / 命令面板：`PlatformIO: Build`、`PlatformIO: Upload` 等。

---

## 專案結構（PlatformIO）

```
practice_code_be_pro/
├── platformio.ini    # PlatformIO 設定（板子、框架、環境）
├── src/
│   └── main.c        # Blink 程式碼（進入點 app_main）
├── lib/              # 自訂函式庫（可選）
├── include/          # 自訂標頭檔（可選）
└── README.md
```

- **程式進入點**：`src/main.c` 的 `app_main()`（使用 ESP-IDF 框架）。
- **板子與框架**：在 `platformio.ini` 的 `[env:esp32dev]` 中可改 `board`、`framework` 等。

---

## 常見問題

| 狀況 | 處理方式 |
|------|----------|
| 找不到 `pio` 指令 | 確認已安裝 PlatformIO IDE 擴充套件，並在專案目錄用「PlatformIO 終端機」或重新開啟終端機。 |
| 燒錄時找不到 COM | 檢查 USB 線、驅動，並在裝置管理員確認 COM 編號，必要時用 `--upload-port COM3` 指定。 |
| 板子沒有內建 LED | 外接 LED：正極接 GPIO 2，負極經 330Ω 電阻接 GND，並確認 `BLINK_GPIO` 為 2。 |
| 想改閃爍速度 | 修改 `src/main.c` 裡的 `500`（單位毫秒），例如改成 `1000` 為每秒閃一次。 |
| 使用 ESP32-S3 / C3 等 | 在 `platformio.ini` 新增對應的 `[env:xxx]`（板子、platform、framework），然後執行 `pio run -e xxx`。 |

---

祝你順利完成第一個 ESP32 程式。
