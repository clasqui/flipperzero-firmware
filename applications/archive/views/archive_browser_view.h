#pragma once

#include <gui/gui_i.h>
#include <gui/view.h>
#include <gui/canvas.h>
#include <gui/elements.h>
#include <furi.h>
#include <storage/storage.h>
#include "../helpers/archive_files.h"
#include "../helpers/archive_favorites.h"

#define MAX_LEN_PX 110
#define MAX_NAME_LEN 255
#define FRAME_HEIGHT 12
#define MENU_ITEMS 4
#define MAX_DEPTH 32

typedef enum {
    ArchiveTabFavorites,
    ArchiveTabLFRFID,
    ArchiveTabSubGhz,
    ArchiveTabNFC,
    ArchiveTabIButton,
    ArchiveTabIrda,
    ArchiveTabBrowser,
    ArchiveTabTotal,
} ArchiveTabEnum;

typedef enum {
    ArchiveBrowserEventFileMenuOpen,
    ArchiveBrowserEventFileMenuClose,
    ArchiveBrowserEventFileMenuRun,
    ArchiveBrowserEventFileMenuPin,
    ArchiveBrowserEventFileMenuRename,
    ArchiveBrowserEventFileMenuDelete,
    ArchiveBrowserEventEnterDir,
    ArchiveBrowserEventExit,
} ArchiveBrowserEvent;

static const uint8_t file_menu_actions[MENU_ITEMS] = {
    [0] = ArchiveBrowserEventFileMenuRun,
    [1] = ArchiveBrowserEventFileMenuPin,
    [2] = ArchiveBrowserEventFileMenuRename,
    [3] = ArchiveBrowserEventFileMenuDelete,
};

typedef struct ArchiveBrowserView ArchiveBrowserView;

typedef void (*ArchiveBrowserViewCallback)(ArchiveBrowserEvent event, void* context);

typedef enum {
    BrowserActionBrowse,
    BrowserActionItemMenu,
    BrowserActionTotal,
} BrowserActionEnum;

struct ArchiveBrowserView {
    View* view;
    ArchiveBrowserViewCallback callback;
    void* context;

    string_t path;
};

typedef struct {
    ArchiveTabEnum tab_idx;
    ArchiveTabEnum last_tab;
    files_array_t files;

    uint8_t depth;
    uint8_t menu_idx;
    bool menu;

    uint16_t idx;
    uint16_t last_idx[MAX_DEPTH];
    uint16_t list_offset;

} ArchiveBrowserViewModel;

void archive_browser_set_callback(
    ArchiveBrowserView* browser,
    ArchiveBrowserViewCallback callback,
    void* context);

View* archive_browser_get_view(ArchiveBrowserView* browser);

ArchiveBrowserView* browser_alloc();
void browser_free(ArchiveBrowserView* browser);