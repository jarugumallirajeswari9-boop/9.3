
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class TipCalculator extends Application {

    @Override
    public void start(Stage stage) {

        Label title = new Label("Tip Calculator");

        Label billLabel = new Label("Enter Bill Amount:");
        TextField billField = new TextField();
        billField.setPromptText("Enter amount");

        Label tipLabel = new Label("Select Tip Percentage:");

        RadioButton tip10 = new RadioButton("10%");
        RadioButton tip15 = new RadioButton("15%");
        RadioButton tip20 = new RadioButton("20%");

        ToggleGroup tipGroup = new ToggleGroup();
        tip10.setToggleGroup(tipGroup);
        tip15.setToggleGroup(tipGroup);
        tip20.setToggleGroup(tipGroup);

        tip15.setSelected(true);

        Label peopleLabel = new Label("Number of People:");
        Spinner<Integer> peopleSpinner =
            new Spinner<>(1, 50, 1);

        Button calculateButton = new Button("Calculate Tip");

        Label resultLabel = new Label("Results will appear here");

        calculateButton.setOnAction(event -> {
            try {
                double bill = Double.parseDouble(
                    billField.getText()
                );

                if (bill < 0) {
                    resultLabel.setText(
                        "Bill amount cannot be negative."
                    );
                    return;
                }

                RadioButton selected =
                    (RadioButton) tipGroup.getSelectedToggle();

                if (selected == null) {
                    resultLabel.setText(
                        "Please select a tip percentage."
                    );
                    return;
                }

                double percentage = Double.parseDouble(
                    selected.getText().replace("%", "")
                );

                int people = peopleSpinner.getValue();

                double tip = bill * percentage / 100;
                double total = bill + tip;
                double perPerson = total / people;

                resultLabel.setText(String.format(
                    "Tip Amount: %.2f%n" +
                    "Total Bill: %.2f%n" +
                    "Amount Per Person: %.2f",
                    tip, total, perPerson
                ));

            } catch (NumberFormatException e) {
                resultLabel.setText(
                    "Please enter a valid bill amount."
                );
            }
        });

        VBox root = new VBox(
            12,
            title,
            billLabel,
            billField,
            tipLabel,
            tip10,
            tip15,
            tip20,
            peopleLabel,
            peopleSpinner,
            calculateButton,
            resultLabel
        );

        root.setPadding(new Insets(20));
        root.setAlignment(Pos.CENTER_LEFT);

        Scene scene = new Scene(root, 350, 500);

        stage.setTitle("JavaFX Tip Calculator");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
