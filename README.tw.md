# CrossPoint Reader

[![Fund contributors](https://img.shields.io/badge/%F0%9F%91%91_Fund_contributors-royalty.dev-BB953A?style=for-the-badge&labelColor=1a1a1a)](https://app.royalty.dev/crosspoint-reader/crosspoint-reader)

CrossPoint 是一款開源的電子書閱讀器韌體 - 由社群構建，完全可修改，且永遠免費。它由不斷壯大的開發者與讀者社群維護，我們相信您的裝置應該聽從您的意願，而不是由製造商為您決定。

**目前運行於：** 基於 ESP32C3 的 Xteink [X4](https://www.xteink.com/products/xteink-x4) 與 [X3](https://www.xteink.com/products/xteink-x3)。

![CrossPoint Reader 運行於 Xteink 裝置](./docs/images/cover.jpg)

> 如果您正打算購買一台 Xteink 裝置，請考慮透過 https://crosspointreader.com 購買 **X3/X4 開發者版本**。CrossPoint 將從每筆銷售中獲得少許分成，以幫助資助開發成本。

## CrossPoint 能做什麼？

- **閱讀引擎**：支援 EPUB 2/3 渲染，包含內嵌樣式選項、圖片處理、連字處理（hyphenation）、字距調整（kerning）、章節導航、腳註、書籤、字典查詢（[StarDict](docs/dictionary.md)）、跳轉至百分比、自動翻頁、方向控制、專注閱讀模式、KOReader 進度同步等。

- **多種格式支援**：原生處理 `.epub`、`.xtc/.xtch`、`.txt` 以及 `.bmp` 格式。

- **螢幕截圖。**

- **自訂字型**：將您喜歡的字型安裝在 SD 卡上。

- **傾斜翻頁（僅限 X3）**。

- **書庫工作流程**：資料夾瀏覽器、隱藏檔案切換、長按刪除、最近閱讀、SD 快取管理。

- **無線工作流程**：

  - 檔案傳輸網頁介面
  - EPUB 最佳化工具
  - 網頁設定 UI/API（可從瀏覽器編輯多項裝置設定）
  - WebSocket 快速上傳
  - WebDAV 處理器
  - AP 模式（熱點）與 STA 模式（加入現有 Wi-Fi），兩者皆附帶 QR 碼輔助
  - Calibre 無線連接流程
  - OPDS 瀏覽器，支援已儲存伺服器（最多 8 個）、搜尋、分頁及直接下載
  - OTA 更新檢查並從 GitHub releases 安裝

- **個人化設定**：多種主題（Classic, Lyra, Lyra Extended, RoundedRaff）、休眠畫面模式（包含透明覆蓋）、前/側邊按鈕重新對應、狀態列控制、電源鍵行為、更新頻率等。

- **在地化**：支援 24 種 UI 語言並持續增加中。支援 RTL（由右至左）。

### 即將推出：

- 更多主題。

- 更多功能！敬請期待。

---

## USB 鎖定的裝置 (Xteink Unlocker)

部分從第三方商店（例如 AliExpress）購買的 Xteink 裝置在出廠時鎖定了 USB 刷機功能。
如果您的裝置被鎖定，在刷入 CrossPoint 之前，您將需要使用 https://crosspointreader.com/#unlock-tool 提供的 **Xteink Unlocker** 工具。

**如果您是直接從 xteink.com 購買裝置，則不需要此工具。** 這些裝置並未被鎖定。

**不確定您的裝置是否被鎖定？** 開機、連接 USB-C 傳輸線，並先嘗試透過網頁刷機工具進行刷機（請參見下方的[安裝韌體](#安裝韌體)）。如果瀏覽器的序列埠選擇器未顯示您的裝置，請在斷定裝置被鎖定前，先嘗試使用不同的 USB 埠或瀏覽器。只有在裝置仍然無法顯示時，才需要使用解鎖工具。

> ### ⚠️ 警告：使用解鎖工具前請閱讀此內容 ⚠️
>
> **解鎖工具中唯一官方支援的韌體是 CrossPoint 與 CrossInk。**
>
> 在 USB 鎖定的裝置上刷入任何其他韌體可能會**導致裝置永久變磚**，或者讓裝置**永久停留在該韌體上且無法恢復**。一旦 USB 刷機功能被重新鎖定，您唯一的恢復途徑就是透過 OTA，如果刷入的韌體不支援 OTA，**您將無法復原**。

## 安裝韌體

### 網頁安裝器（推薦）

1. 透過 USB-C 將裝置連接到電腦，並喚醒/解鎖裝置。
2. 前往 https://crosspointreader.com/#flash-tools，選擇裝置（X3 或 X4），並選擇一個 CrossPoint 官方發布版本。

### 網頁安裝器（指定版本）

1. 透過 USB-C 將裝置連接到電腦，並喚醒/解鎖裝置。
2. 從 [Releases](https://github.com/crosspoint-reader/crosspoint-reader/releases)、本地構建或 CI（持續整合）產物中下載 `firmware.bin`。
3. 前往 https://crosspointreader.com/#flash-tools，選擇裝置（X3 或 X4），點擊 "Custom .bin" 並上傳 `firmware.bin`。

### 恢復至官方韌體

若要恢復至官方韌體，您也可以使用 https://crosspointreader.com/#flash-tools 刷入最新的官方韌體。

### 命令列

1. 安裝 [`esptool`](https://github.com/espressif/esptool)：

```bash
pip install esptool
```

2. 從 [releases 頁面](https://github.com/crosspoint-reader/crosspoint-reader/releases)下載 `firmware.bin`。
3. 透過 USB-C 連接您的裝置。
4. 尋找裝置連接埠。在 Linux 上，連接後執行 `dmesg`。在 macOS 上：

```bash
log stream --predicate 'subsystem == "com.apple.iokit"' --info
```

5. 刷機：

```bash
esptool.py --chip esp32c3 --port /dev/ttyACM0 --baud 921600 write_flash 0x10000 /path/to/firmware.bin
```

請將 `/dev/ttyACM0` 調整為符合您系統的設定。

### 手動安裝

請參見下方的[開發快速入門](#開發快速入門)。

---

## 自訂 SD 卡字型

將您自己的 TTF/OTF 檔案轉換為從 SD 卡載入的 `.cpfont` 檔案。無需重新刷入韌體。

1. 前往 https://crosspointreader.com/fonts 並開啟 "SD-card font builder" 表單。
2. 上傳最多四種樣式（常規、粗體、斜體、粗斜體），設定字型家族名稱、字號大小及 Unicode 範圍。
3. 下載生成的 `.cpfont` 檔案。
4. 將它們複製到 SD 卡的 `/fonts/YourFont/` 目錄下（或 `/.fonts/YourFont/` 來隱藏資料夾）。
5. 在裝置的字型設定中選擇該字型。

轉換過程會未經修改地執行韌體倉庫中的 `lib/EpdFont/scripts/fontconvert_sdcard.py` 腳本，因此輸出結果與本地主機構建的結果一致。

---

## 文件

- [使用指南](./USER_GUIDE.md)
- [網頁伺服器使用說明](./docs/webserver.md)
- [網頁伺服器端點](./docs/webserver-endpoints.md)
- [專案範圍](./SCOPE.md)
- [貢獻指南](./docs/contributing/README.md)
- [觸控與 UI 開發](./docs/contributing/touch-and-ui.md) - 如何在 FreeInkUI 活動基礎上構建新畫面（UiListActivity 及其相關），以及非 Xteink 觸控裝置的建置環境

---

## 開發快速入門

### 先決條件

- [pioarduino](https://github.com/pioarduino/pioarduino) 或 VS Code + pioarduino 擴充元件
- Python 3.8+
- `clang-format` 21
- 支援資料傳輸的 USB-C 傳輸線

### 設定

```bash
git clone --recursive https://github.com/crosspoint-reader/crosspoint-reader
cd crosspoint-reader

# 如果 clone 時沒有加上 --recursive：
git submodule update --init --recursive
```

### Nix/NixOS

Nix/NixOS 使用者可以使用 `nix develop` (flakes) 或 `nix-shell` 進入開發環境：

```bash
nix develop -f nix
# 或
nix-shell nix
```

要刷寫已連接的 ESP32-C3 裝置，請在您的 NixOS 設定中啟用 PlatformIO 的 udev 規則：

```nix
services.udev.packages = with pkgs; [ platformio-core.udev ];
```

重建系統設定後，重新連接裝置或重新載入 udev 規則。

### 構建 / 刷機 / 監控

```bash
pio run --target upload
```

### 貢獻者提交 PR 前的檢查

```bash
./bin/clang-format-fix
pio check -e default
pio run -e default
```

### 除錯

刷入新功能後，建議從序列埠擷取詳細的日誌。

首先，確保已安裝所有必要的 Python 套件：

```python
python3 -m pip install pyserial colorama matplotlib
```

然後執行腳本：

```sh
# 適用於 Linux
# 這已在 Debian 上測試過，應該適用於大多數 Linux 系統。
python3 scripts/debugging_monitor.py

# 適用於 macOS
python3 scripts/debugging_monitor.py /dev/cu.usbmodem2101
```

在 Windows 上可能需要進行少許調整。

---

## 內部運作

CrossPoint Reader 相當積極地將資料快取到 SD 卡上，以盡量減少 RAM 的使用。ESP32-C3 只有大約 380KB 的可用 RAM，因此我們必須非常小心。韌體設計中的許多決定都是基於此限制。

### 資料快取

當一本書的章節首次載入時，它們會被快取到 SD 卡上。後續的載入將由快取提供。此快取目錄位於 SD 卡上的 `.crosspoint`。結構如下：

```text
.crosspoint/
├── epub_<hash>/         # 每本書一個目錄，依內容雜湊值命名
│   ├── progress.bin     # 閱讀進度（章節、頁面等）
│   ├── cover.bmp        # 生成的封面圖片
│   ├── book.bin         # 詮釋資料（metadata）：書名、作者、書脊、目錄
│   ├── css_rules.cache  # 解析後的 CSS 規則快取
│   ├── img_*            # 渲染後的圖片快取檔案
│   └── sections/        # 每章節的排版快取
│       ├── 0.bin
│       ├── 1.bin
│       └── ...
├── settings.json        # 裝置設定
├── state.json           # 恢復/運行時狀態
└── recent.json          # 最近閱讀的書籍清單
```

刪除 `/.crosspoint` 會清除所有快取的詮釋資料，並在下次開啟時強制全面重新生成。透過韌體或網頁介面刪除、覆寫及移動書籍，會清除或重新關聯相符的快取；手動編輯 SD 卡可能會留下過時的快取目錄。

有關內部檔案結構的更多詳細資訊，請參見[檔案格式文件](./docs/file-formats.md)。

---

## 貢獻

歡迎任何貢獻。如果您是程式碼庫的新手，請從[貢獻指南](./docs/contributing/README.md)開始。如需尋找可著手的事項，請查看[想法討論板](https://github.com/crosspoint-reader/crosspoint-reader/discussions/categories/ideas) — 在開始之前請先留言，以免我們重複努力。

這裡的每個人都是志工，所以請保持尊重和耐心。有關治理和社群期望，請參見 [GOVERNANCE.md](./GOVERNANCE.md)。

---

## 社群分支 (Forks)

開源最棒的事情之一就是任何人都能將程式碼帶往不同的方向。如果您需要超出 CrossPoint [範圍](./SCOPE.md)的功能，請查看社群分支：

- [CrossInk](https://github.com/uxjulia/CrossInk) — 排版與閱讀追蹤：仿生閱讀（將單字詞幹加粗以建立注視點）、字間引導點、改善的段落縮排，並將預設字型替換為 ChareInk/Lexend/Bitter。

- [papyrix-reader](https://github.com/bigbag/papyrix-reader) — 新增 FB2 和 MD 格式支援。積極維護並支援阿拉伯文。可透過 SD 卡自訂主題。

- ~~[crosspet](https://github.com/trilwu/crosspet) — 一個越南分支，增加了一個類似電子雞（Tamagotchi）的虛擬小雞，會根據您的閱讀里程碑（閱讀頁數、連續記錄、照顧）而成長。同時包含：閃卡、天氣、番茄鐘計時器及迷你遊戲。~~（停止維護）

- [crosspoint-reader-cjk](https://github.com/aBER0724/crosspoint-reader-cjk) — 專為中、日、韓文閱讀而打造。

- [inx](https://github.com/obijuankenobiii/inx) — 以標籤導航完全重新設計使用者介面。

- ~~[PlusPoint](https://github.com/ngxson/pluspoint-reader) — 支援自訂 JS 應用程式。~~（停止維護）

- [crosspoint-reader-papers3](https://github.com/juicecultus/crosspoint-reader-papers3) — M5Stack Paper S3 的 Crosspoint 移植版本。

- [t5s3-reader](https://github.com/ShallowGreen123/t5s3-reader) — LilyGo T5 ePaper S3 / T5S3 4.7 吋電子紙裝置的 Crosspoint 移植版本。

**注意：** 這些功能中的許多部分隨著時間的推移將會整合進 CrossPoint 中。我們保持較慢的步伐以確保堅若磐石的穩定性，並在更新推送到您的裝置之前消除錯誤。

想要自己動手做一台裝置嗎？請務必查看 [de-link](https://github.com/iandchasse/de-link) 專案。

---

CrossPoint Reader **不隸屬於 Xteink 或任何裝置製造商**。

特別感謝 [diy-esp32-epub-reader](https://github.com/atomic14/diy-esp32-epub-reader)，它啟發了這個專案。
