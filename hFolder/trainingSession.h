#pragma once

#include "event.h"

class TrainingSession : public Event {
public:
    enum class Level { Beginner, Intermediate, Advanced };

    TrainingSession(int id, std::string_view title,
                    std::string_view topic,
                    std::string_view coachName,
                    Level level,
                    int durationMinutes);

    std::string_view getTopic() const;
    std::string_view getCoachName() const;
    Level getLevel() const;
    int getDurationMinutes() const;

    void setTopic(std::string_view newTopic);
    void setCoachName(std::string_view newCoachName);
    void setLevel(Level newLevel);
    void setDurationMinutes(int newDurationMinutes);

    std::string_view getType() const override;
    double calculateMetric() const override;
    std::string_view getMetricName() const override;
    void printEventInformation() const override;

    static std::string_view levelToString(Level level);

private:
    std::string _topic;
    std::string _coachName;
    Level _level;
    int _durationMinutes;
};