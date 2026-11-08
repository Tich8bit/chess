#pragma once

#include "event.h"
#include "collection.h"
#include "coach.h"

class Player;

class TrainingSession : public Event {
public:
    TrainingSession(std::string_view title,
                    std::string_view topic,
                    int durationMinutes,
                    std::shared_ptr<Coach> coach);

    std::string_view getTopic() const;
    int getDurationMinutes() const;
    std::shared_ptr<Coach> getCoach() const;
    const Collection<Player>& getParticipants() const;

    void setTopic(std::string_view newTopic);
    void setDurationMinutes(int newDurationMinutes);
    void setCoach(std::shared_ptr<Coach> newCoach);

    std::string getType() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;

    TrainingSession& operator+=(std::shared_ptr<Player> player);
    TrainingSession& operator-=(std::shared_ptr<Player> player);

private:
    std::string _topic;
    int _durationMinutes;
    std::shared_ptr<Coach> _coach;
    Collection<Player> _participants;
};