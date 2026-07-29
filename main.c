#include <stdio.h>
#include <string.h>

// Global variables for package information
float pkg_mass, route_km, shipping_fee;
int box_length, box_width, box_height;
char delivery_zone[25], service_tier[20], courier_brand[35];
int fragile_status, promo_applied, selected_provider;

// Calculation variables
float base_amount = 0.0;
float priority_fee = 0.0;
float protection_fee = 0.0;
float savings_amount = 0.0;
float route_modifier = 1.0;

// Courier company names
char provider_names[4][30] = {
    "FastShip",
    "QuickPost",
    "SpeedyCourier",
    "GlobalExpress"
};

// Local shipping rates for each company
float local_rates[4] = {5.0, 4.0, 6.0, 7.0};

// International shipping rates for each company
float global_rates[4] = {15.0, 12.0, 18.0, 20.0};

// Function to display welcome screen
void display_welcome_banner() {
    printf("\n");
    printf("****************************************\n");
    printf("SHIPESTIMATOR: Parcel Cost Calculator\n");
    printf("****************************************\n");
    printf("\n>> Calculate precise shipping costs with multiple carriers\n");
    printf(">> Support for domestic and international deliveries\n\n");
}

// Function to collect package details
void gather_shipment_details() {
    printf("--------------------------------------------------\n");
    printf(" SHIPMENT INFORMATION COLLECTION\n");
    printf("--------------------------------------------------\n\n");

    printf("Enter your package weight in kilograms: ");
    scanf("%f", &pkg_mass);

    printf("\nNow enter the dimensions of your package:\n");
    printf(" What is the length in cm? ");
    scanf("%d", &box_length);
    printf(" What is the width in cm? ");
    scanf("%d", &box_width);
    printf(" What is the height in cm? ");
    scanf("%d", &box_height);

    printf("\nHow far do you want to ship it in km? ");
    scanf("%f", &route_km);

    // Validate delivery zone
    int zone_valid = 0;
    while (!zone_valid) {
        printf("\nWhere are you shipping?\n");
        printf(" - Type 'domestic' for local delivery\n");
        printf(" - Type 'international' for overseas delivery\n");
        printf(" Choose zone: ");
        scanf("%s", delivery_zone);

        if (strcmp(delivery_zone, "domestic") == 0 ||
            strcmp(delivery_zone, "international") == 0) {
            zone_valid = 1;
        } else {
            printf(" ERROR: Please enter 'domestic' or 'international' only\n");
        }
    }

    // Validate service tier
    int service_valid = 0;
    while (!service_valid) {
        printf("\nHow fast do you want delivery?\n");
        printf(" - Type 'normal' for regular delivery\n");
        printf(" - Type 'express' for fast delivery\n");
        printf(" Choose service: ");
        scanf("%s", service_tier);

        if (strcmp(service_tier, "normal") == 0 ||
            strcmp(service_tier, "express") == 0) {
            service_valid = 1;
        } else {
            printf(" ERROR: Please enter 'normal' or 'express' only\n");
        }
    }

    // Special handling requirements
    printf("\nIs your package breakable or fragile? (1=Yes, 0=No): ");
    scanf("%d", &fragile_status);

    // Promotional discount
    printf("\nDo you have any coupon or discount code? (1=Yes, 0=No): ");
    scanf("%d", &promo_applied);
}

// Function to select delivery partner
void select_delivery_partner() {
    printf("\n--------------------------------------------------\n");
    printf(" DELIVERY PARTNER SELECTION\n");
    printf("--------------------------------------------------\n");
    printf("\nHere are the shipping companies you can choose from:\n\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s company\n", i + 1, provider_names[i]);
        printf("   For domestic its Rs%.0f per kg and international is Rs%.0f per kg\n\n",
               local_rates[i], global_rates[i]);
    }

    int choice_valid = 0;
    while (!choice_valid) {
        printf("Which company do you want? Enter number 1 to 4: ");
        scanf("%d", &selected_provider);

        if (selected_provider >= 1 && selected_provider <= 4) {
            choice_valid = 1;
            selected_provider--; // convert to array index
            strcpy(courier_brand, provider_names[selected_provider]);
        } else {
            printf("ERROR: Invalid selection. Please choose between 1-4.\n");
        }
    }
}

// Function to calculate dimensional factor
float calculate_dimensional_factor() {
    float volume_cubic_cm = box_length * box_width * box_height;
    float dimensional_weight = volume_cubic_cm / 5000.0; // Custom divisor

    if (dimensional_weight > pkg_mass) {
        return dimensional_weight / pkg_mass;
    }
    return 1.0;
}

// Function to apply route-based adjustments
void apply_zone_adjustments() {
    if (route_km > 1000) {
        route_modifier = 1.5;
        printf("Extra charge because of long distance: 1.5 times more\n");
    } else if (route_km > 500) {
        route_modifier = 1.3;
        printf("Medium range multiplier: 1.3x\n");
    } else if (route_km > 100) {
        route_modifier = 1.1;
        printf("Regional delivery multiplier: 1.1x\n");
    } else {
        route_modifier = 1.0;
        printf("Local delivery: No distance premium\n");
    }
}

// Function to compute all shipping costs
void compute_shipping_costs() {
    printf("\n--------------------------------------------------\n");
    printf(" SHIPPING COST COMPUTATION\n");
    printf("--------------------------------------------------\n");

    // Base calculation
    if (strcmp(delivery_zone, "domestic") == 0) {
        base_amount = pkg_mass * local_rates[selected_provider];
        printf("\nBasic shipping cost: %.2f kg x Rs%.0f = Rs%.2f\n",
               pkg_mass, local_rates[selected_provider], base_amount);
    } else {
        base_amount = pkg_mass * global_rates[selected_provider];
        printf("\nBasic shipping cost: %.2f kg x Rs%.0f = Rs%.2f\n",
               pkg_mass, global_rates[selected_provider], base_amount);
    }

    // Priority service
    if (strcmp(service_tier, "express") == 0) {
        priority_fee = base_amount * 0.5;
        printf("Extra charge for express delivery: Rs%.2f\n", priority_fee);
    }

    // Route adjustments
    apply_zone_adjustments();

    // Dimensional factor
    float dim_factor = calculate_dimensional_factor();
    if (dim_factor > 1.0) {
        base_amount *= dim_factor;
        printf("Dimensional weight adjustment: %.2fx\n", dim_factor);
    }

    // Fragile
    if (fragile_status == 1) {
        protection_fee = base_amount * 0.2;
        printf("Extra charge for fragile handling: Rs%.2f\n", protection_fee);
    }

    // Promo
    if (promo_applied == 1) {
        savings_amount = base_amount * 0.1;
        printf("Money saved from your discount: Rs%.2f\n", savings_amount);
    }

    // Final cost
    shipping_fee = (base_amount + priority_fee + protection_fee) * route_modifier - savings_amount;
    if (shipping_fee < 0) {
        shipping_fee = 0;
    }
}

// Function to generate summary
void generate_cost_summary() {
    printf("\n==========================================\n");
    printf(" HERE IS YOUR FINAL BILL\n");
    printf("==========================================\n");

    printf("\nYour Package Details:\n");
    printf("Weight of your package: %.2fkg\n", pkg_mass);
    printf("Size of your package: %d by %d by %d cm\n", box_length, box_width, box_height);
    printf("How far you are shipping: %.1fkm\n", route_km);
    printf("Where you are shipping: %s\n", delivery_zone);
    printf("What speed you chose: %s\n", service_tier);
    printf("Which company you picked: %s\n", courier_brand);

    printf("\nExtra Services You Selected:\n");
    if (fragile_status == 1) {
        printf("Fragile handling: YES you selected this\n");
    } else {
        printf("Fragile handling: NO you did not select this\n");
    }

    if (promo_applied == 1) {
        printf("Discount applied: YES you have a discount\n");
    } else {
        printf("Discount applied: NO you do not have discount\n");
    }

    printf("\nHow We Calculated Your Bill:\n");
    printf("Basic shipping cost: Rs%.2f\n", base_amount);

    if (strcmp(service_tier, "express") == 0) {
        printf("Extra charge for express delivery: Rs%.2f\n", priority_fee);
    }

    if (fragile_status == 1) {
        printf("Extra charge for fragile handling: Rs%.2f\n", protection_fee);
    }

    if (route_modifier > 1.0) {
        printf("Extra charge because of long distance: %.1f times more\n", route_modifier);
    }

    if (promo_applied == 1) {
        printf("Money saved from your discount: Rs%.2f\n", savings_amount);
    }

    printf("--------------------------------\n");
    printf("FINAL AMOUNT YOU NEED TO PAY: Rs%.2f\n", shipping_fee);
    printf("============================\n");

    // Service category with realistic thresholds
    if (shipping_fee < 50) {
        printf("\nThis is cheap shipping for you\n");
    } else if (shipping_fee < 150) {
        printf("\nThis is regular priced shipping\n");
    } else {
        printf("\nThis is expensive shipping\n");
    }

    printf("\nThanks for using shipestimator that I made!\n");
}

// Main function
int main() {
    display_welcome_banner();
    gather_shipment_details();
    select_delivery_partner();
    compute_shipping_costs();
    generate_cost_summary();

    printf("\n==========================================\n");
    printf(" Session completed successfully! \n");
    printf("==========================================\n\n");

    return 0;
}
