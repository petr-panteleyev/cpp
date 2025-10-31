//  Copyright © 2024-2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

module;

#include <QSettings>
#include <QTime>

module apps.sapper.settings;

import libs.common.localdate;

namespace {

constexpr auto TIME_FORMAT{"{0:%H:%M:%S}"};

const QString LAST_BOARD_SIZE_GROUP{"lastBoardSize"};
const QString BOARD_WIDTH{"width"};
const QString BOARD_HEIGHT{"height"};
const QString BOARD_MINES{"mines"};

const QString SCORES_ARRAY{"scores"};
const QString SCORE_DATE{"date"};
const QString SCORE_TIME{"time"};

constexpr BoardSize DEFAULT_BOARD_SIZE = BoardSize::BIG;

void saveBoardSize(const BoardSize &size, QSettings &settings) {
    settings.setValue(BOARD_WIDTH, size.width());
    settings.setValue(BOARD_HEIGHT, size.height());
    settings.setValue(BOARD_MINES, size.mines());
}

BoardSize loadBoardSize(QSettings &settings) {
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

} // namespace

namespace Settings {

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
        saveBoardSize(s.boardSize_, settings);
        settings.setValue(SCORE_DATE, QString::fromStdString(LocalDate::toIsoString(s.date_)));
        settings.setValue(SCORE_TIME, QString::fromStdString(std::format(TIME_FORMAT, s.seconds_)));
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

        auto date = LocalDate::fromIsoString(settings.value(SCORE_DATE).toString().toStdString());
        if (!date.ok()) {
            continue;
        }

        auto time = QTime::fromString(settings.value(SCORE_TIME).toString(), "HH:mm:ss");
        if (!time.isValid()) {
            continue;
        }
        result.emplace_back(boardSize, date, QTime(0, 0).secsTo(time));
    }

    settings.endArray();
    return result;
}

} // namespace Settings
