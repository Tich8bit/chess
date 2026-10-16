#include "masterClass.h"

MasterClass::MasterClass(int id, std::string_view title,
                         std::string_view guestName,
                         GuestTitle guestTitle,
                         int audienceCount,
                         int durationMinutes)
    : Event(id, title),
      _guestName(guestName),
      _guestTitle(guestTitle),
      _audienceCount(audienceCount),
      _durationMinutes(durationMinutes) {}

std::string_view MasterClass::getGuestName() const { return _guestName; }
MasterClass::GuestTitle MasterClass::getGuestTitle() const { return _guestTitle; }
int MasterClass::getAudienceCount() const { return _audienceCount; }
int MasterClass::getDurationMinutes() const { return _durationMinutes; }

void MasterClass::setGuestName(std::string_view newGuestName) { _guestName = newGuestName; }
void MasterClass::setGuestTitle(GuestTitle newGuestTitle) { _guestTitle = newGuestTitle; }
void MasterClass::setAudienceCount(int newAudienceCount) { _audienceCount = newAudienceCount; }
void MasterClass::setDurationMinutes(int newDurationMinutes) { _durationMinutes = newDurationMinutes; }

std::string_view MasterClass::getType() const { return "Мастер-класс"; }

double MasterClass::calculateMetric() const {
    double coef = 1.5;
    if (_guestTitle == GuestTitle::GM) coef = 3.0;
    else if (_guestTitle == GuestTitle::IM) coef = 2.0;
    return _durationMinutes * coef * _audienceCount / 10.0;
}

std::string_view MasterClass::getMetricName() const { return "Влияние мастер-класса"; }

void MasterClass::printEventInformation() const {
    std::cout << *this
              << " | Гость: " << _guestName
              << " (" << guestTitleToString(_guestTitle) << ")"
              << " | Слушателей: " << _audienceCount
              << " | Длительность: " << _durationMinutes << " мин"
              << "\n";
}

std::string_view MasterClass::guestTitleToString(GuestTitle title) {
    switch (title) {
        case GuestTitle::GM: return "GM";
        case GuestTitle::IM: return "IM";
        case GuestTitle::FM: return "FM";
    }
    return "Неизвестно";
}