#include "trainingSession.h"
#include "player.h"
#include "exceptions/exception.h"

TrainingSession::TrainingSession(int id,
                                 std::string_view title,
                                 std::string_view topic,
                                 int durationMinutes,
                                 std::shared_ptr<Coach> coach)
    : Event(id, title),
      _topic(topic),
      _durationMinutes(durationMinutes),
      _coach(coach) {
    if (topic.empty()) {
        throw InvalidDataException("тема тренировки не может быть пустой");
    }
    if (durationMinutes < 10 || durationMinutes > 300) {
        throw LimitExceededException("длительность должна быть от 10 до 300 минут");
    }
}

std::string_view TrainingSession::getTopic() const { return _topic; }
int TrainingSession::getDurationMinutes() const { return _durationMinutes; }
std::shared_ptr<Coach> TrainingSession::getCoach() const { return _coach; }
const Collection<Player>& TrainingSession::getParticipants() const { return _participants; }

void TrainingSession::setTopic(std::string_view newTopic) {
    if (newTopic.empty()) {
        throw InvalidDataException("тема тренировки не может быть пустой");
    }
    _topic = newTopic;
}

void TrainingSession::setDurationMinutes(int newDurationMinutes) {
    if (newDurationMinutes < 10 || newDurationMinutes > 300) {
        throw LimitExceededException("длительность должна быть от 10 до 300 минут");
    }
    _durationMinutes = newDurationMinutes;
}

void TrainingSession::setCoach(std::shared_ptr<Coach> newCoach) { _coach = newCoach; }

std::string TrainingSession::getType() const { return "Тренировка"; }

double TrainingSession::calculateMetric() const {
    return _durationMinutes * (1.0 + _participants.size() * 0.1);
}

std::string TrainingSession::getMetricName() const { return "Педагогическая нагрузка"; }

void TrainingSession::printInfo(std::ostream& os) const {
    Event::printInfo(os);
    os << "\n  Тема: " << _topic
       << "\n  Тренер: " << (_coach ? _coach->getFullName() : "не назначен")
       << "\n  Длительность: " << _durationMinutes << " мин"
       << "\n  Участников: " << _participants.size();
}

TrainingSession& TrainingSession::operator+=(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    if (auto existing = _participants.find([&player](const std::shared_ptr<Player>& p) {
        return p == player;
    })) {
        throw DuplicateIdException("игрок " + player->getFullName() + " уже записан на тренировку");
    }
    _participants.add(player);
    return *this;
}

TrainingSession& TrainingSession::operator-=(std::shared_ptr<Player> player) {
    if (!player) {
        throw InvalidDataException("пустой указатель на игрока");
    }
    if (size_t removed = _participants.removeIf([&player](const std::shared_ptr<Player>& p) {
        return p == player;
    }); removed == 0) {
        throw ObjectNotFoundException("игрок " + player->getFullName() + " не записан на тренировку");
    }
    return *this;
}