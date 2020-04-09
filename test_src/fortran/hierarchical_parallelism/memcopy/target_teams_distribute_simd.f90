program target_teams_distribute_simd

    implicit none

    REAL, ALLOCATABLE :: A(:)  
    REAL, ALLOCATABLE :: B(:)
  
    INTEGER :: L = 5
    INTEGER :: i

    INTEGER :: S
    S = L
     
    ALLOCATE(A(S), B(S) )
    CALL RANDOM_NUMBER(B)
  
    
    !$OMP TARGET TEAMS DISTRIBUTE SIMD   MAP(FROM: A) MAP(TO: B) 


    DO i = 1 , L 

    

    A( i ) = B( i )
 
     

    END DO

    !$OMP END TARGET TEAMS DISTRIBUTE SIMD
    

    IF (ANY(ABS(A - B) > EPSILON(A) )) THEN
        write(*,*)  'Wrong value', MAXVAL(ABS(A-B)), 'max difference'
        call exit(1)
    ENDIF

    DEALLOCATE(A,B)

end program target_teams_distribute_simd