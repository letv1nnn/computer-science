//              *** Description ***
// Chain of Responsibility is a behavioral design pattern
// that lets you pass requests along a chain of handlers.
// Upon receiving a request, each handler decides either to
// process the request or to pass it to the next handler in the chain.

import java.util.Objects;

public class ChainOfResponsibility {
    public static void main(String[] args) {
        Approver teamLead = new TeamLead();
        Approver manager = new DepartmentManager();
        Approver director = new Director();

        teamLead.setNext(manager);
        manager.setNext(director);

        Expense e1 = new Expense(500);
        Expense e2 = new Expense(3000);
        Expense e3 = new Expense(10000);

        teamLead.approve(e1);
        teamLead.approve(e2);
        teamLead.approve(e3);
    }
}

// request class
class Expense {
    private final double amount;

    public Expense(double amount) {
        this.amount = amount;
    }

    public double getAmount() {
        return amount;
    }
}

// handler interface
interface Approver {
    void setNext(Approver next);
    void approve(Expense expense);
}

abstract class AbstractApprover implements Approver {
    protected Approver next;

    public void setNext(Approver next) {
        this.next = Objects.requireNonNull(next, "next approve cannot be null");
    }
}

// concrete handlers
class TeamLead extends AbstractApprover {
    @Override
    public void approve(Expense expense) {
        if (expense.getAmount() <= 1000) {
            System.out.println("Team Lead approved $" + expense.getAmount());
        } else if (next != null) {
            next.approve(expense);
        }
    }
}

class DepartmentManager extends AbstractApprover {
    @Override
    public void approve(Expense expense) {
        if (expense.getAmount() <= 5000)
            System.out.println("Department Manager approved $" + expense.getAmount());
        else if (next != null)
            next.approve(expense);
    }
}

class Director extends AbstractApprover {
    @Override
    public void approve(Expense expense) {
        System.out.println("Director approved €" + expense.getAmount());
    }
}