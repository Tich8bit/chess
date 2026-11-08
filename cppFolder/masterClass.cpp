#include "masterClass.h"
#include "exceptions/exception.h"

MasterClass::MasterClass(int id, std::string_view title,
                         std::string_view guestName,
                         GuestTitle guestTitle,
                         int audienceCount,
                         int durationMinutes)
    : Event(id, title),
      _guestName(guestName),
      _guestTitle(guestTitle),
      _audienceCount(audienceCount),
      _durationMinutes(durationMinutes) {
    if (guestName.empty()) {
        throw InvalidDataException("Имя гостя не может быть пустым");
    }
    if (audienceCount < 1 || audienceCount > 1000) {
        throw LimitExceededException("Количество слушателей должно быть от 1 до 1000");
    }
    if (durationMinutes < 10 || durationMinutes > 300) {
        throw LimitExceededException("Длительность мастер-класса должна быть от 10 до 300 минут");
    }
}

std::string_view MasterClass::getGuestName() const { return _guestName; }
MasterClass::GuestTitle MasterClass::getGuestTitle() const { return _guestTitle; }
int MasterClass::getAudienceCount() const { return _audienceCount; }
int MasterClass::getDurationMinutes() const { return _durationMinutes; }

void MasterClass::setGuestName(std::string_view newGuestName) {
    if (newGuestName.empty()) {
        throw InvalidDataException("Имя гостя не может быть пустым");
    }
    _guestName = newGuestName;
}

void MasterClass::setGuestTitle(GuestTitle newGuestTitle) { _guestTitle = newGuestTitle; }

void MasterClass::setAudienceCount(int newAudienceCount) {
    if (newAudienceCount < 1 || newAudienceCount > 1000) {
        throw LimitExceededException("Количество слушателей должно быть от 1 до 1000");
    }
    _audienceCount = newAudienceCount;
}

void MasterClass::setDurationMinutes(int newDurationMinutes) {
    if (newDurationMinutes < 10 || newDurationMinutes > 300) {
        throw LimitExceededException("Длительность мастер-класса должна быть от 10 до 300 минут");
    }
    _durationMinutes = newDurationMinutes;
}

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