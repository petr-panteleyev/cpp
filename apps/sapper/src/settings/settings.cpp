/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "settings.h"
#include "qsettings.h"
#include <QSettings>

namespace Settings {

static const QString LAST_BOARD_SIZE_GROUP{"lastBoardSize"};
static const QString BOARD_WIDTH{"width"};
static const QString BOARD_HEIGHT{"height"};
static const QString BOARD_MINES{"mines"};

static const QString SCORES_ARRAY{"scores"};
static const QString SCORE_DATE{"date"};
static const QString SCORE_TIME{"time"};

static const BoardSize DEFAULT_BOARD_SIZE = BoardSize::BIG;

static void saveBoardSize(const BoardSize &size, QSettings &settings) {
    settings.setValue(BOARD_WIDTH, size.width());
    settings.setValue(BOARD_HEIGHT, size.height());
    settings.setValue(BOARD_MINES, size.mines());
}

static BoardSize loadBoardSize(QSettings &settings) {
    bool ok;
    auto width = settings.value(BOARD_WIDTH, BoardSize::BIG.width()).toInt(&ok);
    if (!ok) {
        return DEFAULT_BOARD_SIZE;
    }
    auto height = settings.value(BOARD_HEIGHT, BoardSize::BIG.height()).toInt(&ok);
    if (!ok) {
        return DEFAULT_BOARD_SIZE;
    }
    auto mines = settings.value(BOARD_MINES, BoardSize::BIG.mines()).toInt(&ok);
    if (!ok) {
        return DEFAULT_BOARD_SIZE;
    }
    return BoardSize::boardSize(width, height, mines);
}

void setLastBoardSize(const BoardSize &boardSize) {
    QSettings settings;

    settings.beginGroup(LAST_BOARD_SIZE_GROUP);
    saveBoardSize(boardSize, settings);
    settings.endGroup();
    settings.sync();
}

BoardSize getLastBoardSize() {
    QSettings settings;

    settings.beginGroup(LAST_BOARD_SIZE_GROUP);
    auto boardSize = loadBoardSize(settings);
    settings.endGroup();
    return boardSize;
}

void setGameScores(const std::span<GameScore> &scores) {
    QSettings settings;
    settings.beginWriteArray(SCORES_ARRAY, scores.size());

    auto index = 0;
    for (const auto &s : scores) {
        settings.setArrayIndex(index++);
        saveBoardSize(s.boardSize, settings);
        settings.setValue(SCORE_DATE, s.date.toString("yyyy-MM-dd"));
        settings.setValue(SCORE_TIME, s.time.toString("HH:mm:ss.zzz"));
    }

    settings.endArray();
}

std::vector<GameScore> getGameScores() {
    QSettings settings;
    std::vector<GameScore> result;

    auto size = settings.beginReadArray(SCORES_ARRAY);
    for (auto i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        auto boardSize = loadBoardSize(settings);
        auto date = QDate::fromString(settings.value(SCORE_DATE).toString(), "yyyy-MM-dd");
        if (!date.isValid()) {
            continue;
        }
        auto time = QTime::fromString(settings.value(SCORE_TIME).toString(), "HH:mm:ss.zzz");
        if (!time.isValid()) {
            continue;
        }
        result.push_back(GameScore{.boardSize = boardSize, .date = date, .time = time});
    }

    settings.endArray();
    return result;
}

} // namespace Settings
