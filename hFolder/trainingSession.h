#pragma once
#include "event.h"
#include "collection.h"
#include "member.h"
#include "coach.h"

class TrainingSession : public Event {
public:
    TrainingSession(int id, std::string_view title, std::string_view topic, int durationMinutes, std::shared_ptr<Coach> coach);
    
    std::string_view getTopic() const;
    int getDurationMinutes() const;
    std::shared_ptr<Coach> getCoach() const;
    const Collection<Member>& getParticipants() const;
    
    std::string getType() const override;
    double calculateMetric() const override;
    std::string getMetricName() const override;
    void printInfo(std::ostream& os) const override;
    
    TrainingSession& operator+=(std::shared_ptr<Member> player);
    
private:
    std::string _topic;
    int _durationMinutes;
    std::shared_ptr<Coach> _coach;
    Collection<Member> _participants;
};