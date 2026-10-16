#pragma once

#include "event.h"

class MasterClass : public Event {
public:
    enum class GuestTitle { GM, IM, FM };

    MasterClass(int id, std::string_view title,
                std::string_view guestName,
                GuestTitle guestTitle,
                int audienceCount,
                int durationMinutes);

    std::string_view getGuestName() const;
    GuestTitle getGuestTitle() const;
    int getAudienceCount() const;
    int getDurationMinutes() const;

    void setGuestName(std::string_view newGuestName);
    void setGuestTitle(GuestTitle newGuestTitle);
    void setAudienceCount(int newAudienceCount);
    void setDurationMinutes(int newDurationMinutes);

    std::string_view getType() const override;
    double calculateMetric() const override;
    std::string_view getMetricName() const override;
    void printEventInformation() const override;

    static std::string_view guestTitleToString(GuestTitle title);

private:
    std::string _guestName;
    GuestTitle _guestTitle;
    int _audienceCount;
    int _durationMinutes;
};