#include "trainingSession.h"
#include "player.h"

TrainingSession::TrainingSession(int id, std::string_view title, std::string_view topic, int durationMinutes, std::shared_ptr<Coach> coach)
    : Event(id, title), _topic(topic), _durationMinutes(durationMinutes), _coach(coach) {}

std::string_view TrainingSession::getTopic() const { return _topic; }
int TrainingSession::getDurationMinutes() const { return _durationMinutes; }
std::shared_ptr<Coach> TrainingSession::getCoach() const { return _coach; }
const Collection<Member>& TrainingSession::getParticipants() const { return _participants; }

std::string TrainingSession::getType() const { return "Тренировка"; }
double TrainingSession::calculateMetric() const { return _durationMinutes; }
std::string TrainingSession::getMetricName() const { return "Нагрузка"; }

void TrainingSession::printInfo(std::ostream& os) const {
    Event::printInfo(os);
    os << "\n  Тема: " << _topic << "\n  Участников: " << _participants.size() << "\n";
}

TrainingSession& TrainingSession::operator+=(std::shared_ptr<Member> player) {
    _participants.add(player);
    if (_coach) {
        if (auto p = std::dynamic_pointer_cast<Player>(player)) {
            p->applyTrainingEffect(_coach->getSpecialization());
        }
    }
    return *this;
}