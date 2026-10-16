#include "trainingSession.h"

TrainingSession::TrainingSession(int id, std::string_view title,
                                 std::string_view topic,
                                 std::string_view coachName,
                                 Level level,
                                 int durationMinutes)
    : Event(id, title),
      _topic(topic),
      _coachName(coachName),
      _level(level),
      _durationMinutes(durationMinutes) {}

std::string_view TrainingSession::getTopic() const { return _topic; }
std::string_view TrainingSession::getCoachName() const { return _coachName; }
TrainingSession::Level TrainingSession::getLevel() const { return _level; }
int TrainingSession::getDurationMinutes() const { return _durationMinutes; }

void TrainingSession::setTopic(std::string_view newTopic) { _topic = newTopic; }
void TrainingSession::setCoachName(std::string_view newCoachName) { _coachName = newCoachName; }
void TrainingSession::setLevel(Level newLevel) { _level = newLevel; }
void TrainingSession::setDurationMinutes(int newDurationMinutes) { _durationMinutes = newDurationMinutes; }

std::string_view TrainingSession::getType() const { return "Тренировка"; }

double TrainingSession::calculateMetric() const {
    double coef = 1.0;
    if (_level == Level::Intermediate) coef = 1.5;
    else if (_level == Level::Advanced) coef = 2.0;
    return _durationMinutes * coef;
}

std::string_view TrainingSession::getMetricName() const { return "Педагогическая нагрузка"; }

void TrainingSession::printEventInformation() const {
    std::cout << *this
              << " | Тема: " << _topic
              << " | Тренер: " << _coachName
              << " | Уровень: " << levelToString(_level)
              << " | Длительность: " << _durationMinutes << " мин"
              << "\n";
}

std::string_view TrainingSession::levelToString(Level level) {
    switch (level) {
        case Level::Beginner:     return "Начинающие";
        case Level::Intermediate: return "Средний";
        case Level::Advanced:     return "Продвинутый";
    }
    return "Неизвестно";
}