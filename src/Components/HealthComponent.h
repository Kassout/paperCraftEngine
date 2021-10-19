#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

/// Structure responsible for holding the data linked to the health of the entity.
/// @file HealthComponent.h
/// @author Maxime Héliot
/// @version 0.1.0 18/10/2021
struct HealthComponent {
    /// Integer value representing the health, expressed in percentage, of the entity
    int healthPercentage;

    /// @brief Default HealthComponent constructor
    /// @details Base constructor of the HealthComponent class taking a health percentage value as parameters.
    HealthComponent(int healthPercentage = 0): healthPercentage(healthPercentage) {}
};

#endif // HEALTHCOMPONENT_H //
