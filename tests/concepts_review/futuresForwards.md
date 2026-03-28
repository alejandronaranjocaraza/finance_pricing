# Futures & Forwards – Conceptual

## A. Forwards vs Futures

1. In theory, forward and futures prices are often presented as the same.  
   In practice, why do futures and forwards have different values?  
   *(Give at least two mechanisms.)*

   <i>
   1. Theoretically, the main reason futures and forwards can have different values is that interest rates can be stochastic in nature. This has a direct impact on future pricing, as the returns are settled daily. For example, if interest rates have a strong positive correlation with the underlying asset, this will raise future prices above forward prices: increase in spot price will lead to increase in returns from going long on futures, and returns will then be invested at risk free rate (higher now), which will also result in higher returns. This would shift future prices above forward prices.
   2. In practice, other factors, such as tax rates, liquidity and transaction costs also have a strong impact on differences between forwars and futures. For example, closing out a Forward is much harder than closing out a Future, as Forwards require an Over The Counter (OTC) negotiation.
   </i>

2. How does daily marking-to-market affect the economic value of a futures contract compared to a forward?  
   *(Think about interest rates and timing of cash flows.)*

   <i>
   1. Theoretically, the main reason futures and forwards can have different values is that interest rates can be stochastic in nature. This has a direct impact on future pricing, as the returns are settled daily. For example, if interest rates have a strong positive correlation with the underlying asset, this will raise future prices above forward prices: increase in spot price will lead to increase in returns from going long on futures, and returns will then be invested at risk free rate (higher now), which will also result in higher returns. This would shift future prices above forward prices.
   </i>

3. Under what interest-rate environment would a futures price tend to be higher than the corresponding forward price? Why?

    <i>
    Then the correlation between interest rates and the underlying asset's price is positive and close to 1, future prices will tend to be higher: daily settlements on future earnings will be invested at higher rates, while borrowing to cover losses will be at a lower interest rate. When the correlation is between interest and asset price is negative, the inverse argument can be made (harder to cover losses and less yield from investments on losses.
    </i>
---

## B. Cost of Carry & Pricing Logic

4. Conceptually define **cost of carry**. What components does it include for:
   - (a) a non-dividend-paying asset  
   - (b) an equity index

   <i>
   Cost of carry is the cost of holding a specific asset (storage costs, financing costs and opportunity cost) minus earnings from holding the asset (dividend payments, convenience yield depending on convention). In the case of a non-dividend-paying asset, the coast of carry is the risk-free-rate (r). This is the opportunity cost of not using the same money to invest on risk-free securities. On the other hand, investement on equities, usually carried out thorugh index funds / exchange trade funds does yield dividends. The cost of carry is therefore the risk-free-rate minus dividend yield (r-q).
   </i>



5. Why does the no-arbitrage forward/futures price grow at (roughly) the risk-free rate for an equity index?
   *(What assumption about dividends is being made?)*

   <i>
   For an equity-index, a consistent compounding dividend yield is often considered. In this case, the forward/future price grows at roughly the risk-free rate minus dividend-yield. The underlying assumption is that, if this does not hold, arbitrage will happen: shorting underlying asset and going long on future/forward to generate income on negative index returns and shorting future/forward + going long on asset to generate income on positive index returns.
   </i>

6. What is a **cash-and-carry arbitrage**?  
   Describe the steps without using equations.

   <i>
   Cash and carry arbitrage is a market neutral stretegy that involves going short/long on an asset and long/short on future. It attempts to exploit differences in asset's spot market and futures/forwards market. This is the main argument used to derive the general futures/forwards pricing equation (with no-arbitrage assumption).
   If the pricing equation does not hold, then arbitrage is possible by shorting the asset and going long on future/forward or buying the asset and shorting the future/forward:
   If forwad/future is overpriced:
    - Short forward to sell asset at F0.
    - Borrow money at risk-free rate and use it buy the asset at S0
    - At maturity, earnings are F0 - S0 * exp(r)
   If forwad/future is underpriced:
    - Go long on forward to buy asset as F0.
    - Short asset: Borrow and sell asset for S0. Invest earnings at risk-free-rate.
    - At maturity buy asset at F0 to give back to lender. Eearnings are S0 * exp(r) - F0.
   </i>

---

## C. Convenience Yield & Term Structure

7. What is **convenience yield**, and why does it not usually apply to financial assets like equity indices?

    <i>
    Convenience yield is the non-monetary benefit derived from having an asset in hand. This issually does not apply to financial assets, as the benefits from having them in hand (such as dividends) are monetary. An example of convenience yield on a consumption asset is having crude oil barrels physically, which in turn makes it available in seasons of high demand or low market availability.
    </i>

8. How can a positive convenience yield lead to **backwardation** even when interest rates are positive?

    <i>
    Note: Total Return = (Spot Price Change Return) + (Roll Yield) + (Collateral Yield)
        * Roll Yield: Yield from futre/forward price change towards underlying asset spot price as maturity date aproaches.
        * Collateral Yield: Yield from interest on posted collateral.
    Positive convenience yield means that having the asset in hand is valuable. Interest rates DO increae future/forward prices, as the benefit of investing capital with the risk free rate, instead of buying an asset is more profitable, but high convenience yield can offset this effect by providing an instrinsic (hidden) benefit from holding the asset.
    Backwardation, where future/forward prices are bellow asset spot price and roll upwards as maturity aproaches, are influences through high convenience yields, as it means that the value of  holding the asset physically instead of secureing future ownership is more valuable.
    </i>

9. Give an intuitive explanation of **contango vs backwardation** that does NOT rely on formulas.

    <i>
    - Backwardation: Price of forward/future is below price of underlying asset price and rolls upwards.
        Occures, for example, when there is a market shoratage of the underlying asset, or risk free interest is low and dividends are high.
    - Contango: Price of forward/future is above price of underlying asset price and rolls downwards.
        Occurs when, for example, there is high risk free interest rate, low dividends, or when there are no worries about future shortages of the asset.
    </i>

---

## D. Roll Yield & Returns

10. What is **roll yield**?  
    When is it positive and when is it negative?

    <i>
    Roll yield is the return froma a forward/future contract because of price changes towards the underlying asset / short term contract price as maturity aproahces.
    It is negative when convenience yield is low and cost of carry is high (contango).
    It is positive when convenience yield is high and cost of carry is low (backwardation).
    </i>

11. Why can a futures investor lose money even if the spot price of the underlying asset is unchanged?

    <i>
    Roll yield + collateral yield can cause future returns to deviate even if underlying asset spot price remains unchagned.
    </i>

12. Explain the decomposition:  
    **Total futures return = spot return + roll yield + collateral yield**  
    *(What does each term represent economically?)*

    <i>
    Future returns are caused by three main factors:
    - Spot return: Return generated from changes in underlying asset spot price.
        * Higher spot price -> Higher future price
    - Roll yield: Return resulting from future price rolling towards asset price as maturity aproaches
        * Asset price > Future price -> Positive roll yield
    - Collateral yield: Yield from interest on collateral
    </i>

---

## E. Index Futures (MSCI relevance)

13. How is an equity index futures price linked to the spot index and dividends?  
    Conceptually, what is the futures buyer “missing out on”?

    <i>
    An equity-futures-index's underlying asset is a market index (not the actual stock).
    A futures buyer is missing out on dividends payed by the index.
    </i>

14. Why are index futures widely used instead of futures on individual stocks for hedging portfolios?

    <i>
    Index futures are used instead of futures on individual stocks for hedging portfolios because of convenience and ease of transaction. Individual assests can be iliquid and transaction costs (spreads) can accumulate. Index futures are generally settled in cash, which removes necessity to buy and sell hundreds of individual assets.
    </i>

15. How can index futures be used to **equitize cash**, and why is this relevant for asset managers and MSCI clients?

    <i>
    Index futures allow for easy exposure (low transaction cost, liquidity, cash efficiency as only margin is required) to equity returns without buying assets/equity. This keeps cash liquid without incurring opportunity cost on interest (cash drag). Asset managers can have high cash flows from reblancing, dividends, fund inflows and outflows. For example, a MSCI-World-Indexed benchmarked fund can use futures on MSCI-World to track the fund.
    </i>

---

## F. Hedging & Risk

16. When hedging an equity portfolio with index futures, what risks remain even if the hedge ratio is correct?  
    *(Name at least two.)*

    <i>
    1. Basis risk: Tracking error caused by mismatch (even if slight) between future underlying asset and hedged asset.
    2. Idyosyncratic risk: Risk that is native to the specific asset and unrelated to systematic events.
    3. Factor risk: Risk related to systematic factors, regime changes for example.
    </i>

17. What is **basis risk** in the context of index futures hedging?

    <i>
    Basis risk is the risk caused by diffeerences in a future's underlying assets and the assets being hedged. There is always basis risk when correlation between hedged asset and underlying asset is not perfect.
    </i>

18. How do futures help reduce **tracking error** for ETFs or index funds?

    <i>
    Futures help reduce tracking error by mitigating cash drag: equitizing cash allows consistent, low risk, returns with low transaction costs and while maintaining liquidity.
    </i>

---

## G. High-signal Interview Wrap-up

19. If markets are arbitrage-free, why do futures prices still move independently of spot prices intraday?

    <i>
    1. Markets are not arbitrage free. There are always arbitrageurs that, sometimes through automated systems, look to benefit from deviations from these opportunities.
    2. No arbitrage is generally observed long term. Short term deviations always occur because of supply/demand shocks, cost of carry, convenience yield fluctuations, speculation, etc.
    </i>

20. In one sentence: why do futures exist if forwards already allow the same payoff at maturity?

    <i>
    Futures are traded through clearing-house as intermediary. This makes future transactions more standerdized and rebalancing efficient. Daily settlement and rebalancing + margin accounts and marking to market (with initial margin and maintenance margin) also makes trades less prone to default. Futures are therefore easyer to trade and close out.
    </i>
