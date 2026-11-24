#include "i18n.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

const char *g_i18n_lang = nullptr;
static bool g_i18n_initialized = false;

static void i18n_ensure_init(void) {
    if (!g_i18n_initialized) {
        g_i18n_initialized = true;
        i18n_init();
    }
}

// ---- English (default, used as key fallback) ----
static const char *en_stack       = "Stack";
static const char *en_source      = "Source";
static const char *en_breakpoints = "Breakpoints";
static const char *en_registers   = "Registers";
static const char *en_watch       = "Watch";
static const char *en_locals      = "Locals";
static const char *en_commands    = "Commands";
static const char *en_data        = "Data";
static const char *en_struct      = "Struct";
static const char *en_files       = "Files";
static const char *en_console     = "Console";
static const char *en_log         = "Log";
static const char *en_thread      = "Thread";
static const char *en_exe         = "Exe";
static const char *en_cmdsearch   = "CmdSearch";
static const char *en_asm         = "ASM";

// Commands
static const char *en_cmd_run            = "Run";
static const char *en_cmd_run_paused     = "Run paused";
static const char *en_cmd_kill           = "Kill";
static const char *en_cmd_restart_gdb    = "Restart GDB";
static const char *en_cmd_load_coredump  = "Load Last Coredump";
static const char *en_cmd_connect        = "Connect";
static const char *en_cmd_continue       = "Continue";
static const char *en_cmd_step_over      = "Step over";
static const char *en_cmd_step_out_block = "Step out of block";
static const char *en_cmd_step_in        = "Step in";
static const char *en_cmd_step_outer     = "Step into outer";
static const char *en_cmd_step_out       = "Step out";
static const char *en_cmd_rev_cont       = "Reverse continue";
static const char *en_cmd_rev_step_over  = "Reverse step over";
static const char *en_cmd_rev_step_in    = "Reverse step in";
static const char *en_cmd_pause          = "Pause";
static const char *en_cmd_toggle_bp      = "Toggle breakpoint";
static const char *en_cmd_sync_gvim      = "Sync with gvim";
static const char *en_cmd_get_pwd        = "Ask GDB for PWD";
static const char *en_cmd_toggle_asm     = "Toggle disassembly";
static const char *en_cmd_set_asm_mode   = "Set disassembly mode";
static const char *en_cmd_add_watch      = "Add watch";
static const char *en_cmd_inspect_line   = "Inspect line";
static const char *en_cmd_copy_layout    = "Copy Layout to Clipboard";

// Dialogs
static const char *en_dialog_ok              = "OK";
static const char *en_dialog_cancel          = "Cancel";
static const char *en_dialog_save            = "Save";
static const char *en_dialog_connect         = "Connect";
static const char *en_dialog_kill            = "Kill";
static const char *en_dialog_overwrite       = "Overwrite";
static const char *en_dialog_add             = "Add";
static const char *en_dialog_save_open       = "Save and open";

static const char *en_err_no_wdir     = "Couldn't get the working directory.";
static const char *en_err_connect_rem = "Connect to remote target?";
static const char *en_err_kill_tgt    = "Kill debugging target?";
static const char *en_err_win_notfound = "Couldn't find the window '%s'.";
static const char *en_err_asm_mode    = "Select the disassembly mode:";
static const char *en_asm_disonly     = "Disassembly only";
static const char *en_asm_withsrc     = "With source";
static const char *en_asm_srccentric  = "Source centric";
static const char *en_err_save_path   = "Save to file\nPath:";
static const char *en_err_addr_var    = "Couldn't get the address of the variable.";
static const char *en_err_data_notopen= "The data window is not open.\nThe watch log cannot be created.";
static const char *en_watch_log_cfg   = "-- Watch logger settings --\nExpressions to evaluate (separate with semicolons):";
static const char *en_err_watchpoint  = "Couldn't set the watchpoint.";
static const char *en_log_setup       = "The log has been setup in the data window.";
static const char *en_err_save_path2  = "Path:";
static const char *en_err_open_write  = "Could not open the file for writing!";
static const char *en_err_exec_path   = "The executable path is invalid.";
static const char *en_warn_projgf     = ".project.gf already exists in the current directory.";
static const char *en_info_saved_ex   = "Saved executable settings!";
static const char *en_bitmap_add      = "Add bitmap\n\nPointer to bits: (32bpp, RR GG BB AA)\nWidth:\nHeight:\nStride: (optional)";
static const char *en_no_preset_cmds  = "No preset commands found in config file!";
static const char *en_exec_path_lbl   = "Path to executable:";
static const char *en_exec_args_lbl   = "Command line arguments:";
static const char *en_save_expr       = "Save expressions to file?";
static const char *en_dialog_save_expr= "Expressions to save:";
static const char *en_err_goto_addr   = "Enter address expression:";
static const char *en_goto            = "Goto";
static const char *en_err_mem_access  = "Cannot access memory at address 0.";
static const char *en_err_expr_addr   = "Expression did not evaluate to an address.";
static const char *en_src_not_found   = "Source information was not found for this function.";
static const char *en_profile_load1   = "Profile data could not be loaded (1).\nConsult the guide.";
static const char *en_profile_load2   = "Profile data could not be loaded (2).\nConsult the guide.";
static const char *en_save_bitmap     = "Save to file\nPath:";
static const char *en_unable_open_f   = "Unable to open file for writing.";

// ---- Chinese translations ----
static const char *zh_stack       = "调用栈";
static const char *zh_source      = "源码";
static const char *zh_breakpoints = "断点";
static const char *zh_registers   = "寄存器";
static const char *zh_watch       = "监视";
static const char *zh_locals      = "局部变量";
static const char *zh_commands    = "命令";
static const char *zh_data        = "数据";
static const char *zh_struct      = "结构体";
static const char *zh_files       = "文件";
static const char *zh_console     = "控制台";
static const char *zh_log         = "日志";
static const char *zh_thread      = "线程";
static const char *zh_exe         = "可执行";
static const char *zh_cmdsearch   = "命令搜索";
static const char *zh_asm         = "汇编";

// Commands (zh)
static const char *zh_cmd_run            = "运行";
static const char *zh_cmd_run_paused     = "暂停运行";
static const char *zh_cmd_kill           = "终止";
static const char *zh_cmd_restart_gdb    = "重启 GDB";
static const char *zh_cmd_load_coredump  = "加载上次 Core dump";
static const char *zh_cmd_connect        = "连接";
static const char *zh_cmd_continue       = "继续";
static const char *zh_cmd_step_over      = "单步跳过";
static const char *zh_cmd_step_out_block = "跳出代码块";
static const char *zh_cmd_step_in        = "单步入";
static const char *zh_cmd_step_outer     = "跳入外层函数";
static const char *zh_cmd_step_out       = "跳出函数";
static const char *zh_cmd_rev_cont       = "反向继续";
static const char *zh_cmd_rev_step_over  = "反向单步跳过";
static const char *zh_cmd_rev_step_in    = "反向单步入";
static const char *zh_cmd_pause          = "暂停";
static const char *zh_cmd_toggle_bp      = "切换断点";
static const char *zh_cmd_sync_gvim      = "同步 GVim";
static const char *zh_cmd_get_pwd        = "获取工作目录";
static const char *zh_cmd_toggle_asm     = "切换汇编视图";
static const char *zh_cmd_set_asm_mode   = "设置汇编模式";
static const char *zh_cmd_add_watch      = "添加监视";
static const char *zh_cmd_inspect_line   = "检查当前行";
static const char *zh_cmd_copy_layout    = "复制布局到剪贴板";

// Dialogs (zh)
static const char *zh_dialog_ok              = "确定";
static const char *zh_dialog_cancel          = "取消";
static const char *zh_dialog_save            = "保存";
static const char *zh_dialog_connect         = "连接";
static const char *zh_dialog_kill            = "终止";
static const char *zh_dialog_overwrite       = "覆盖";
static const char *zh_dialog_add             = "添加";
static const char *zh_dialog_save_open       = "保存并打开";

static const char *zh_err_no_wdir     = "无法获取工作目录。";
static const char *zh_err_connect_rem = "连接到远程目标？";
static const char *zh_err_kill_tgt    = "终止调试目标？";
static const char *zh_err_win_notfound = "找不到窗口 '%s'。";
static const char *zh_err_asm_mode    = "选择反汇编模式：";
static const char *zh_asm_disonly     = "仅汇编";
static const char *zh_asm_withsrc     = "含源码";
static const char *zh_asm_srccentric  = "源码为主";
static const char *zh_err_save_path   = "保存到文件\n路径：";
static const char *zh_err_addr_var    = "无法获取变量地址。";
static const char *zh_err_data_notopen= "数据窗口未打开。\n无法创建监视日志。";
static const char *zh_watch_log_cfg   = "-- 监视日志设置 --\n要计算的表达式（用分号分隔）：";
static const char *zh_err_watchpoint  = "无法设置监视点。";
static const char *zh_log_setup       = "日志已在数据窗口中设置完毕。";
static const char *zh_err_save_path2  = "路径：";
static const char *zh_err_open_write  = "无法打开文件进行写入！";
static const char *zh_err_exec_path   = "可执行文件路径无效。";
static const char *zh_warn_projgf     = ".project.gf 已存在于当前目录中。";
static const char *zh_info_saved_ex   = "已保存可执行文件设置！";
static const char *zh_bitmap_add      = "添加位图\n\n位图指针：(32bpp, RR GG BB AA)\n宽度：\n高度：\n步幅：（可选）";
static const char *zh_no_preset_cmds  = "配置文件中未找到预设命令！";
static const char *zh_exec_path_lbl   = "可执行文件路径：";
static const char *zh_exec_args_lbl   = "命令行参数：";
static const char *zh_save_expr       = "是否保存表达式到文件？";
static const char *zh_dialog_save_expr= "要保存的表达式：";
static const char *zh_err_goto_addr   = "输入地址表达式：";
static const char *zh_goto            = "跳转到";
static const char *zh_err_mem_access  = "无法访问地址 0 处的内存。";
static const char *zh_err_expr_addr   = "表达式未计算为地址。";
static const char *zh_src_not_found   = "未找到该函数的源代码信息。";
static const char *zh_profile_load1   = "无法加载性能数据 (1)。\n请查阅指南。";
static const char *zh_profile_load2   = "无法加载性能数据 (2)。\n请查阅指南。";
static const char *zh_save_bitmap     = "保存到文件\n路径：";
static const char *zh_unable_open_f   = "无法打开文件进行写入。";

// ---- Japanese translations ----
static const char *ja_stack       = "スタック";
static const char *ja_source      = "ソース";
static const char *ja_breakpoints = "ブレイクポイント";
static const char *ja_registers   = "レジスタ";
static const char *ja_watch       = "ウォッチ";
static const char *ja_locals      = "ローカル";
static const char *ja_commands    = "コマンド";
static const char *ja_data        = "データ";
static const char *ja_struct      = "構造体";
static const char *ja_files       = "ファイル";
static const char *ja_console     = "コンソール";
static const char *ja_log         = "ログ";
static const char *ja_thread      = "スレッド";
static const char *ja_exe         = "実行可能";
static const char *ja_cmdsearch   = "コマンド検索";
static const char *ja_asm         = "ASM";

static const char *ja_cmd_run            = "実行";
static const char *ja_cmd_run_paused     = "停止実行";
static const char *ja_cmd_kill           = "終了";
static const char *ja_cmd_restart_gdb    = "GDB 再起動";
static const char *ja_cmd_load_coredump  = "前回のコア.dump読み込み";
static const char *ja_cmd_connect        = "接続";
static const char *ja_cmd_continue       = "継続";
static const char *ja_cmd_step_over      = "ステップオーバー";
static const char *ja_cmd_step_out_block = "ブロックから抜け出す";
static const char *ja_cmd_step_in        = "ステップイン";
static const char *ja_cmd_step_outer     = "外側の関数へ入り込む";
static const char *ja_cmd_step_out       = "ステップアウト";
static const char *ja_cmd_rev_cont       = "逆継続";
static const char *ja_cmd_rev_step_over  = "逆ステップオーバー";
static const char *ja_cmd_rev_step_in    = "逆ステップイン";
static const char *ja_cmd_pause          = "一時停止";
static const char *ja_cmd_toggle_bp      = "ブレイクポイント切替";
static const char *ja_cmd_sync_gvim      = "GVim と同期";
static const char *ja_cmd_get_pwd        = "作業ディレクトリを取得";
static const char *ja_cmd_toggle_asm     = "アセンブリ切替";
static const char *ja_cmd_set_asm_mode   = "アセンブリモード設定";
static const char *ja_cmd_add_watch      = "ウォッチ追加";
static const char *ja_cmd_inspect_line   = "行を inspect";
static const char *ja_cmd_copy_layout    = "レイアウトをクリップボードにコピー";

static const char *ja_dialog_ok              = "OK";
static const char *ja_dialog_cancel          = "キャンセル";
static const char *ja_dialog_save            = "保存";
static const char *ja_dialog_connect         = "接続";
static const char *ja_dialog_kill            = "終了";
static const char *ja_dialog_overwrite       = "上書き";
static const char *ja_dialog_add             = "追加";
static const char *ja_dialog_save_open       = "保存して開く";

static const char *ja_err_no_wdir     = "作業ディレクトリを取得できません。";
static const char *ja_err_connect_rem = "リモートターゲットに接続しますか？";
static const char *ja_err_kill_tgt    = "デバッグターゲットを終了しますか？";
static const char *ja_err_win_notfound = "ウィンドウ '%s' が見つかりません。";
static const char *ja_err_asm_mode    = "逆アセンブリモードを選択：";
static const char *ja_asm_disonly     = "ディスアセンブリのみ";
static const char *ja_asm_withsrc     = "ソース付き";
static const char *ja_asm_srccentric  = "ソース中心";
static const char *ja_err_save_path   = "ファイルに保存\nパス：";
static const char *ja_err_addr_var    = "変数のアドレスを取得できません。";
static const char *ja_err_data_notopen= "データウィンドウが開いていません。\nウォッチログを作成できません。";
static const char *ja_watch_log_cfg   = "-- ウォッチログ設定 --\n評価する式（セミコロン区切り）：";
static const char *ja_err_watchpoint  = "ウォッチポイントを設定できません。";
static const char *ja_log_setup       = "ログがデータウィンドウに設定されました。";
static const char *ja_err_save_path2  = "パス：";
static const char *ja_err_open_write  = "ファイルを開けません。";
static const char *ja_err_exec_path   = "実行可能ファイルのパスが無効です。";
static const char *ja_warn_projgf     = ".project.gf は既にカレントディレクトリに存在します。";
static const char *ja_info_saved_ex   = "実行可能ファイル設定を保存しました！";
static const char *ja_bitmap_add      = "ビットマップ追加\n\nビットポインタ：(32bpp, RR GG BB AA)\n幅：\n高さ：\nストライド：（任意）";
static const char *ja_no_preset_cmds  = "設定ファイルにプリセットコマンドが見つかりません！";
static const char *ja_exec_path_lbl   = "実行可能ファイルのパス：";
static const char *ja_exec_args_lbl   = "コマンドライン引数：";
static const char *ja_save_expr       = "式をファイルに保存しますか？";
static const char *ja_dialog_save_expr= "保存する式：";
static const char *ja_err_goto_addr   = "アドレス式を入力：";
static const char *ja_goto            = "ジャンプ";
static const char *ja_err_mem_access  = "アドレス 0 のメモリにアクセスできません。";
static const char *ja_err_expr_addr   = "式がアドレスを評価しませんでした。";
static const char *ja_src_not_found   = "この関数のソース情報は見つかりませんでした。";
static const char *ja_profile_load1   = "プロファイルデータをロードできません (1)。\nガイドを参照してください。";
static const char *ja_profile_load2   = "プロファイルデータをロードできません (2)。\nガイドを参照してください。";
static const char *ja_save_bitmap     = "ファイルに保存\nパス：";
static const char *ja_unable_open_f   = "ファイルを開けません。";

// ---- additional strings ----
static const char *zh_add_bitmap_dots = "添加位图...";
static const char *zh_save_to_file_dots = "保存到文件...";
static const char *zh_save_to_file_pad = "保存到文件       \n路径：";
static const char *zh_bitmap_prompt = "添加位图\n\n%l\n\n位图指针：";
static const char *zh_start = "开始";
static const char *zh_ask_gdb_dir = "询问 GDB 获取工作目录";
static const char *zh_save_proj = "保存到 .project.gf";
static const char *zh_usage = "用法：%s [GDB 参数]\n\n";
static const char *zh_source_help = "切换汇编：Ctrl+D\n切换汇编模式：Ctrl+M\n跳转到：Ctrl+Shift+G";
static const char *zh_full_help = "用法：%s [GDB 参数]\n\n"
		"GDB 参数：在此传入任意 GDB 参数，它们会被转发给 GDB。\n\n"
		"更多信息请查看 README：https://github.com/nakst/gf/blob/master/README.md.\n";
static const char *zh_language = "语言...";
static const char *zh_select_language = "选择语言：";
static const char *zh_language_changed = "语言已更改。部分标签将在重启 gf2 后更新。";
static const char *zh_shell_running = "正在执行 shell 命令 \"%s\"...\n";
static const char *zh_shell_result = "（退出码：%d；耗时：%ds）\n";

// Additional UI strings.
static const char *zh_delete = "删除";
static const char *zh_disable = "禁用";
static const char *zh_enable = "启用";
static const char *zh_auto = "自动";
static const char *zh_refresh = "刷新";
static const char *zh_resize_columns = "调整列宽";
static const char *zh_fill_window = "填满窗口";
static const char *zh_to_cwd = "-> 工作目录";
static const char *zh_to_active_file = "-> 当前文件";
static const char *zh_edit_expr = "编辑表达式";
static const char *zh_copy_value = "复制值到剪贴板\tCtrl+C";
static const char *zh_log_writes = "记录地址写入...";
static const char *zh_break_writes = "地址写入时中断";
static const char *zh_add_entry_addr = "添加地址条目\tCtrl+E";
static const char *zh_view_source_addr = "查看地址源码\tCtrl+G";
static const char *zh_save_as = "另存为...";
static const char *zh_no_exprs = "没有可显示的表达式。";
static const char *zh_bmp_width = "无法计算宽度。";
static const char *zh_bmp_height = "无法计算高度。";
static const char *zh_bmp_pointer = "无法计算指针。";
static const char *zh_bmp_pointer_addr = "图像位指针看起来不是地址！";
static const char *zh_bmp_stride = "无法计算步幅。";
static const char *zh_bmp_read = "无法读取图像位！";
static const char *zh_disasm_fail = "无法加载反汇编。\n按 Ctrl+D 返回源码视图。";
static const char *zh_type_struct = "输入要查看布局的结构体名称。";
static const char *zh_type_search = "在此输入搜索 \nGDB 命令描述。";
static const char *zh_col_index = "索引\t函数\t位置\t地址";
static const char *zh_col_bp = "文件\t行\t启用\t条件\t命中";
static const char *zh_col_thread = "ID\t名称\t帧";
static const char *zh_menu = "菜单";
static const char *zh_bitmap = "位图";

static const char *ja_add_bitmap_dots = "ビットマップ追加...";
static const char *ja_save_to_file_dots = "ファイルに保存...";
static const char *ja_save_to_file_pad = "ファイルに保存       \nパス：";
static const char *ja_bitmap_prompt = "ビットマップ追加\n\n%l\n\nビットポインタ：";
static const char *ja_start = "開始";
static const char *ja_ask_gdb_dir = "作業ディレクトリを GDB に尋ねる";
static const char *ja_save_proj = ".project.gf に保存";
static const char *ja_usage = "使い方: %s [GDB 引数]\n\n";
static const char *ja_source_help = "アセンブリ切替: Ctrl+D\nアセンブリモード切替: Ctrl+M\nジャンプ: Ctrl+Shift+G";
static const char *ja_full_help = "使い方: %s [GDB 引数]\n\n"
		"GDB 引数: 任意の GDB 引数をここに渡すと、GDB に転送されます。\n\n"
		"詳細は README を参照: https://github.com/nakst/gf/blob/master/README.md.\n";
static const char *ja_language = "言語...";
static const char *ja_select_language = "言語を選択：";
static const char *ja_language_changed = "言語を変更しました。一部のラベルは gf2 の再起動後に更新されます。";
static const char *ja_shell_running = "シェルコマンド \"%s\" を実行中...\n";
static const char *ja_shell_result = "（終了コード: %d; 時間: %ds）\n";

static const char *ja_delete = "削除";
static const char *ja_disable = "無効";
static const char *ja_enable = "有効";
static const char *ja_auto = "自動";
static const char *ja_refresh = "更新";
static const char *ja_resize_columns = "列幅を調整";
static const char *ja_fill_window = "ウィンドウに合わせる";
static const char *ja_to_cwd = "-> 作業ディレクトリ";
static const char *ja_to_active_file = "-> アクティブファイル";
static const char *ja_edit_expr = "式を編集";
static const char *ja_copy_value = "値をクリップボードにコピー\tCtrl+C";
static const char *ja_log_writes = "アドレスへの書き込みをログ...";
static const char *ja_break_writes = "アドレスへの書き込みで停止";
static const char *ja_add_entry_addr = "アドレスのエントリを追加\tCtrl+E";
static const char *ja_view_source_addr = "アドレスのソースを表示\tCtrl+G";
static const char *ja_save_as = "名前を付けて保存...";
static const char *ja_no_exprs = "表示する式がありません。";
static const char *ja_bmp_width = "幅を評価できません。";
static const char *ja_bmp_height = "高さを評価できません。";
static const char *ja_bmp_pointer = "ポインタを評価できません。";
static const char *ja_bmp_pointer_addr = "画像ビットのポインタがアドレスではありません！";
static const char *ja_bmp_stride = "ストライドを評価できません。";
static const char *ja_bmp_read = "画像ビットを読み取れません！";
static const char *ja_disasm_fail = "逆アセンブリをロードできません。\nCtrl+D でソースビューに戻ります。";
static const char *ja_type_struct = "レイアウトを表示する構造体の名前を入力してください。";
static const char *ja_type_search = "ここに入力して検索 \nGDB コマンドの説明。";
static const char *ja_col_index = "番号\t関数\t位置\tアドレス";
static const char *ja_col_bp = "ファイル\t行\t有効\t条件\tヒット";
static const char *ja_col_thread = "ID\t名前\tフレーム";
static const char *ja_menu = "メニュー";
static const char *ja_bitmap = "ビットマップ";

// ---- lookup table ----
struct Entry { const char *key; const char *en; const char *zh; const char *ja; } table[] = {
    // windows
    { "Stack",      en_stack,       zh_stack,       ja_stack      },
    { "Source",     en_source,      zh_source,      ja_source     },
    { "Breakpoints",en_breakpoints, zh_breakpoints, ja_breakpoints},
    { "Registers",  en_registers,   zh_registers,   ja_registers  },
    { "Watch",      en_watch,       zh_watch,       ja_watch      },
    { "Locals",     en_locals,      zh_locals,      ja_locals     },
    { "Commands",   en_commands,    zh_commands,    ja_commands   },
    { "Data",       en_data,        zh_data,        ja_data       },
    { "Struct",     en_struct,      zh_struct,      ja_struct     },
    { "Files",      en_files,       zh_files,       ja_files      },
    { "Console",    en_console,     zh_console,     ja_console    },
    { "Log",        en_log,         zh_log,         ja_log        },
    { "Thread",     en_thread,      zh_thread,      ja_thread     },
    { "Exe",        en_exe,         zh_exe,         ja_exe        },
    { "CmdSearch",  en_cmdsearch,   zh_cmdsearch,   ja_cmdsearch  },
    { "ASM",        en_asm,         zh_asm,         ja_asm        },
    // commands
    { "Run",                         en_cmd_run,            zh_cmd_run,            ja_cmd_run           },
    { "Run paused",                  en_cmd_run_paused,     zh_cmd_run_paused,     ja_cmd_run_paused    },
    { "Kill",                        en_cmd_kill,           zh_cmd_kill,           ja_cmd_kill          },
    { "Restart GDB",                 en_cmd_restart_gdb,    zh_cmd_restart_gdb,    ja_cmd_restart_gdb   },
    { "Load Last Coredump",          en_cmd_load_coredump,  zh_cmd_load_coredump,  ja_cmd_load_coredump },
    { "Connect",                     en_cmd_connect,        zh_cmd_connect,        ja_cmd_connect       },
    { "Continue",                    en_cmd_continue,       zh_cmd_continue,       ja_cmd_continue      },
    { "Step over",                   en_cmd_step_over,      zh_cmd_step_over,      ja_cmd_step_over     },
    { "Step out of block",           en_cmd_step_out_block, zh_cmd_step_out_block, ja_cmd_step_out_block},
    { "Step in",                     en_cmd_step_in,        zh_cmd_step_in,        ja_cmd_step_in       },
    { "Step into outer",             en_cmd_step_outer,     zh_cmd_step_outer,     ja_cmd_step_outer    },
    { "Step out",                    en_cmd_step_out,       zh_cmd_step_out,       ja_cmd_step_out      },
    { "Reverse continue",            en_cmd_rev_cont,       zh_cmd_rev_cont,       ja_cmd_rev_cont      },
    { "Reverse step over",           en_cmd_rev_step_over,  zh_cmd_rev_step_over,  ja_cmd_rev_step_over },
    { "Reverse step in",             en_cmd_rev_step_in,    zh_cmd_rev_step_in,    ja_cmd_rev_step_in   },
    { "Pause",                       en_cmd_pause,          zh_cmd_pause,          ja_cmd_pause         },
    { "Toggle breakpoint",           en_cmd_toggle_bp,      zh_cmd_toggle_bp,      ja_cmd_toggle_bp     },
    { "Sync with gvim",              en_cmd_sync_gvim,      zh_cmd_sync_gvim,      ja_cmd_sync_gvim     },
    { "Ask GDB for PWD",             en_cmd_get_pwd,        zh_cmd_get_pwd,        ja_cmd_get_pwd       },
    { "Toggle disassembly",          en_cmd_toggle_asm,     zh_cmd_toggle_asm,     ja_cmd_toggle_asm    },
    { "Set disassembly mode",        en_cmd_set_asm_mode,   zh_cmd_set_asm_mode,   ja_cmd_set_asm_mode  },
    { "Add watch",                   en_cmd_add_watch,      zh_cmd_add_watch,      ja_cmd_add_watch     },
    { "Inspect line",                en_cmd_inspect_line,   zh_cmd_inspect_line,   ja_cmd_inspect_line  },
    { "Copy Layout to Clipboard",    en_cmd_copy_layout,    zh_cmd_copy_layout,    ja_cmd_copy_layout   },
    // dialogs buttons
    { "OK",       en_dialog_ok,       zh_dialog_ok,       ja_dialog_ok      },
    { "Cancel",   en_dialog_cancel,   zh_dialog_cancel,   ja_dialog_cancel  },
    { "Save",     en_dialog_save,     zh_dialog_save,     ja_dialog_save    },
    { "Connect",  en_dialog_connect,  zh_dialog_connect,  ja_dialog_connect },
    { "Kill",     en_dialog_kill,     zh_dialog_kill,     ja_dialog_kill    },
    { "Overwrite",en_dialog_overwrite,zh_dialog_overwrite,ja_dialog_overwrite},
    { "Add",      en_dialog_add,      zh_dialog_add,      ja_dialog_add     },
    { "Save and open", en_dialog_save_open, zh_dialog_save_open, ja_dialog_save_open },
    // messages
    { "Couldn't get the working directory.", en_err_no_wdir,     zh_err_no_wdir,     ja_err_no_wdir     },
    { "Connect to remote target?",          en_err_connect_rem,  zh_err_connect_rem,  ja_err_connect_rem  },
    { "Kill debugging target?",             en_err_kill_tgt,     zh_err_kill_tgt,     ja_err_kill_tgt     },
    { "Couldn't find the window '%s'.",     en_err_win_notfound, zh_err_win_notfound, ja_err_win_notfound },
    { "Select the disassembly mode:",       en_err_asm_mode,     zh_err_asm_mode,     ja_err_asm_mode     },
    { "Disassembly only",                   en_asm_disonly,      zh_asm_disonly,      ja_asm_disonly      },
    { "With source",                        en_asm_withsrc,      zh_asm_withsrc,      ja_asm_withsrc      },
    { "Source centric",                     en_asm_srccentric,   zh_asm_srccentric,   ja_asm_srccentric   },
    { "Save to file\nPath:",                en_err_save_path,    zh_err_save_path,    ja_err_save_path    },
    { "Couldn't get the address of the variable.", en_err_addr_var, zh_err_addr_var, ja_err_addr_var },
    { "The data window is not open.\nThe watch log cannot be created.", en_err_data_notopen, zh_err_data_notopen, ja_err_data_notopen },
    { "-- Watch logger settings --\nExpressions to evaluate (separate with semicolons):",
                                            en_watch_log_cfg,    zh_watch_log_cfg,    ja_watch_log_cfg    },
    { "Couldn't set the watchpoint.",       en_err_watchpoint,   zh_err_watchpoint,   ja_err_watchpoint   },
    { "The log has been setup in the data window.", en_log_setup, zh_log_setup,    ja_log_setup        },
    { "Path:",                              en_err_save_path2,   zh_err_save_path2,   ja_err_save_path2   },
    { "Could not open the file for writing!", en_err_open_write,zh_err_open_write,  ja_err_open_write   },
    { "The executable path is invalid.",    en_err_exec_path,    zh_err_exec_path,    ja_err_exec_path    },
    { ".project.gf already exists in the current directory.", en_warn_projgf, zh_warn_projgf, ja_warn_projgf },
    { "Saved executable settings!",         en_info_saved_ex,    zh_info_saved_ex,    ja_info_saved_ex    },
    { "Add bitmap\n\nPointer to bits: (32bpp, RR GG BB AA)\nWidth:\nHeight:\nStride: (optional)",
                                            en_bitmap_add,     zh_bitmap_add,     ja_bitmap_add     },
    { "No preset commands found in config file!", en_no_preset_cmds, zh_no_preset_cmds, ja_no_preset_cmds },
    { "Path to executable:",                en_exec_path_lbl,  zh_exec_path_lbl,  ja_exec_path_lbl  },
    { "Command line arguments:",            en_exec_args_lbl,  zh_exec_args_lbl,  ja_exec_args_lbl  },
    { "Save expressions to file?",          en_save_expr,      zh_save_expr,      ja_save_expr      },
    { "Expressions to save:",               en_dialog_save_expr,zh_dialog_save_expr,ja_dialog_save_expr},
    { "Enter address expression:",          en_err_goto_addr,  zh_err_goto_addr,  ja_err_goto_addr  },
    { "Goto",                               en_goto,           zh_goto,           ja_goto           },
    { "Cannot access memory at address 0.", en_err_mem_access, zh_err_mem_access, ja_err_mem_access },
    { "Expression did not evaluate to an address.", en_err_expr_addr, zh_err_expr_addr, ja_err_expr_addr },
    { "Source information was not found for this function.", en_src_not_found, zh_src_not_found, ja_src_not_found },
    { "Profile data could not be loaded (1).\nConsult the guide.", en_profile_load1, zh_profile_load1, ja_profile_load1 },
    { "Profile data could not be loaded (2).\nConsult the guide.", en_profile_load2, zh_profile_load2, ja_profile_load2 },
    { "Save to file\nPath:",                en_save_bitmap,    zh_save_bitmap,    ja_save_bitmap    },
    { "Unable to open file for writing.",   en_unable_open_f,  zh_unable_open_f,  ja_unable_open_f  },
    { "Add bitmap...",                     "Add bitmap...",   zh_add_bitmap_dots, ja_add_bitmap_dots },
    { "Save to file...",                   "Save to file...", zh_save_to_file_dots, ja_save_to_file_dots },
    { "Save to file       \nPath:",        "Save to file       \nPath:", zh_save_to_file_pad, ja_save_to_file_pad },
    { "Add bitmap\n\n%l\n\nPointer to bits: (32bpp, RR GG BB AA)",
                                           "Add bitmap\n\n%l\n\nPointer to bits: (32bpp, RR GG BB AA)", zh_bitmap_prompt, ja_bitmap_prompt },
    { "Start",                             "Start",           zh_start,          ja_start          },
    { "Ask GDB for working directory",     "Ask GDB for working directory", zh_ask_gdb_dir, ja_ask_gdb_dir },
    { "Save to .project.gf",               "Save to .project.gf", zh_save_proj, ja_save_proj },
    { "Usage: %s [GDB args]\n\nGDB args: Pass any GDB arguments here, they will be forwarded to GDB.\n\nFor more information, view the README at https://github.com/nakst/gf/blob/master/README.md.\n",
                                           "Usage: %s [GDB args]\n\nGDB args: Pass any GDB arguments here, they will be forwarded to GDB.\n\nFor more information, view the README at https://github.com/nakst/gf/blob/master/README.md.\n", zh_full_help, ja_full_help },
    { "Usage: %s [GDB args]",              "Usage: %s [GDB args]", zh_usage, ja_usage },
    { "Toggle disassembly: Ctrl+D\nToggle disassembly mode: Ctrl+M\nGoto: Ctrl+Shift+G",
                                           "Toggle disassembly: Ctrl+D\nToggle disassembly mode: Ctrl+M\nGoto: Ctrl+Shift+G", zh_source_help, ja_source_help },
    { "Language...",                       "Language...",             zh_language,       ja_language       },
    { "Select language:",                  "Select language:",        zh_select_language,ja_select_language },
    { "Language changed. Some labels update after restarting gf2.\n%f%B",
                                           "Language changed. Some labels update after restarting gf2.\n%f%B", zh_language_changed, ja_language_changed },
    { "Running shell command \"%s\"...\n",  "Running shell command \"%s\"...\n", zh_shell_running, ja_shell_running },
    { "(exit code: %d; time: %ds)\n",      "(exit code: %d; time: %ds)\n",      zh_shell_result, ja_shell_result },
    { "Delete",                            "Delete",            zh_delete,           ja_delete           },
    { "Disable",                           "Disable",           zh_disable,          ja_disable          },
    { "Enable",                            "Enable",            zh_enable,           ja_enable           },
    { "Auto",                              "Auto",              zh_auto,             ja_auto             },
    { "Refresh",                           "Refresh",           zh_refresh,          ja_refresh          },
    { "Resize columns",                    "Resize columns",    zh_resize_columns,   ja_resize_columns   },
    { "Fill window",                       "Fill window",       zh_fill_window,      ja_fill_window      },
    { "-> cwd",                            "-> cwd",            zh_to_cwd,           ja_to_cwd           },
    { "-> active file",                    "-> active file",    zh_to_active_file,   ja_to_active_file   },
    { "Edit expression",                   "Edit expression",   zh_edit_expr,        ja_edit_expr        },
    { "Copy value to clipboard\tCtrl+C",   "Copy value to clipboard\tCtrl+C", zh_copy_value, ja_copy_value },
    { "Log writes to address...",          "Log writes to address...", zh_log_writes, ja_log_writes },
    { "Break on writes to address",        "Break on writes to address", zh_break_writes, ja_break_writes },
    { "Add entry for address\tCtrl+E",     "Add entry for address\tCtrl+E", zh_add_entry_addr, ja_add_entry_addr },
    { "View source at address\tCtrl+G",    "View source at address\tCtrl+G", zh_view_source_addr, ja_view_source_addr },
    { "Save as...",                        "Save as...",        zh_save_as,          ja_save_as          },
    { "No expressions to display.",        "No expressions to display.", zh_no_exprs, ja_no_exprs },
    { "Could not evaluate width.",         "Could not evaluate width.", zh_bmp_width, ja_bmp_width },
    { "Could not evaluate height.",        "Could not evaluate height.", zh_bmp_height, ja_bmp_height },
    { "Could not evaluate pointer.",       "Could not evaluate pointer.", zh_bmp_pointer, ja_bmp_pointer },
    { "Pointer to image bits does not look like an address!", "Pointer to image bits does not look like an address!", zh_bmp_pointer_addr, ja_bmp_pointer_addr },
    { "Could not evaluate stride.",        "Could not evaluate stride.", zh_bmp_stride, ja_bmp_stride },
    { "Could not read the image bits!",    "Could not read the image bits!", zh_bmp_read, ja_bmp_read },
    { "Disassembly could not be loaded.\nPress Ctrl+D to return to source view.",
                                           "Disassembly could not be loaded.\nPress Ctrl+D to return to source view.", zh_disasm_fail, ja_disasm_fail },
    { "Type the name of a struct to view its layout.", "Type the name of a struct to view its layout.", zh_type_struct, ja_type_struct },
    { "Type here to search \nGDB command descriptions.", "Type here to search \nGDB command descriptions.", zh_type_search, ja_type_search },
    { "Index\tFunction\tLocation\tAddress", "Index\tFunction\tLocation\tAddress", zh_col_index, ja_col_index },
    { "File\tLine\tEnabled\tCondition\tHit", "File\tLine\tEnabled\tCondition\tHit", zh_col_bp, ja_col_bp },
    { "ID\tName\tFrame",                   "ID\tName\tFrame",   zh_col_thread,       ja_col_thread       },
    { "Menu",                              "Menu",              zh_menu,             ja_menu             },
    { "Bitmap",                            "Bitmap",            zh_bitmap,           ja_bitmap           },
};
#define ENTRY_COUNT (sizeof(table)/sizeof(table[0]))

static const char *lookup(const char *key,
                          const char *en, const char *zh, const char *ja) {
    if (!g_i18n_lang || g_i18n_lang[0] == '\0') return en;
    if (strcasecmp(g_i18n_lang, "zh") == 0 || strcasecmp(g_i18n_lang, "zh-cn") == 0 ||
        strcasecmp(g_i18n_lang, "zh-hans") == 0 || strcasecmp(g_i18n_lang, "zh-tw") == 0 ||
        strcasecmp(g_i18n_lang, "zh-hant") == 0 || strcasecmp(g_i18n_lang, "zh-hk") == 0 ||
        strcasecmp(g_i18n_lang, "cn") == 0)    return zh ? zh : en;
    if (strcasecmp(g_i18n_lang, "ja") == 0)  return ja ? ja : en;
    return en;
}

const char *T(const char *key) {
    if (!key) return "";
    i18n_ensure_init();

    size_t keyLength = strlen(key);

    for (size_t i = 0; i < ENTRY_COUNT; i++) {
        if (strcmp(table[i].key, key) == 0) {
            return lookup(key, table[i].en, table[i].zh, table[i].ja);
        }
    }

    // Compose translations for keys with runtime suffixes, e.g.
    // "Run\tShift+F5" or "Couldn't get the working directory.\n%f%B".
    const Entry *best = nullptr;
    size_t bestLength = 0;
    for (size_t i = 0; i < ENTRY_COUNT; i++) {
        size_t length = strlen(table[i].key);
        if (length < keyLength && length > bestLength &&
                strncmp(table[i].key, key, length) == 0) {
            best = &table[i];
            bestLength = length;
        }
    }

    if (best) {
        const char *translated = lookup(best->key, best->en, best->zh, best->ja);
        if (translated != best->en) {
            size_t translatedLength = strlen(translated);
            char *result = (char *) malloc(translatedLength + (keyLength - bestLength) + 1);
            if (result) {
                memcpy(result, translated, translatedLength);
                memcpy(result + translatedLength, key + bestLength, keyLength - bestLength + 1);
                return result;
            }
        }
    }

    return key;
}

void i18n_init(void) {
    // Only auto-detect from the environment when no language was set explicitly
    // (e.g. from the config file), so a saved preference always wins.
    if (g_i18n_lang) return;
    const char *lc = getenv("LC_ALL");
    if (!lc) lc = getenv("LC_MESSAGES");
    if (!lc) lc = getenv("LANG");
    i18n_set_lang(lc);
}

void i18n_set_lang(const char *lang) {
    // Store a copy so we own the lifetime.
    free((void *)g_i18n_lang);
    if (lang && lang[0]) {
        // Normalize: take only the language part before '_' or '.'
        char buf[32];
        int n = 0;
        while (n < 31 && lang[n] && lang[n] != '_' && lang[n] != '.' && lang[n] != '-') {
            buf[n] = (char) tolower((unsigned char) lang[n]);
            n++;
        }
        buf[n] = '\0';

        if (0 == strcmp(buf, "zh")) {
            // Preserve traditional Chinese script when the locale specifies it.
            if (strcasestr(lang, "hant") || strcasestr(lang, "tw") || strcasestr(lang, "hk")) {
                g_i18n_lang = strdup("zh-hant");
            } else {
                g_i18n_lang = strdup("zh");
            }
        } else {
            g_i18n_lang = strdup(buf);
        }
    } else {
        g_i18n_lang = strdup("en");
    }
}

const char *i18n_get_lang(void) {
    i18n_ensure_init();
    return g_i18n_lang ? g_i18n_lang : "en";
}

bool i18n_is_cjk(void) {
    i18n_ensure_init();
    if (!g_i18n_lang) return false;
    return strcasecmp(g_i18n_lang, "zh") == 0 || strcasecmp(g_i18n_lang, "zh-cn") == 0 ||
           strcasecmp(g_i18n_lang, "zh-hans") == 0 || strcasecmp(g_i18n_lang, "zh-tw") == 0 ||
           strcasecmp(g_i18n_lang, "zh-hant") == 0 || strcasecmp(g_i18n_lang, "zh-hk") == 0 ||
           strcasecmp(g_i18n_lang, "cn") == 0 || strcasecmp(g_i18n_lang, "ja") == 0;
}
